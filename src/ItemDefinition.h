#pragma once
#include <map>
#include <vector>
#include "Minecraft/Items/Item.h" 
#include "Minecraft/Util/SharedPtr.h"
#include "Minecraft/Items/VanillaItems.h"
#include "Minecraft/Items/ItemRegistry.h"

struct ItemGroup {
	const std::string iconItem;
	const std::string langKey;
	CreativeItemCategory category;
	const std::vector<std::string> itemIdentifiers;
};

class ItemEntryBase {
protected:
	WeakPtr<Item> itemWeakPtr;

public:
	virtual ~ItemEntryBase() = default;
	virtual void registerItem() = 0;
	virtual void initializeClient() = 0;
	virtual WeakPtr<Item> getCurrentWeak() = 0;
};

template<typename T>
class ItemEntry : ItemEntryBase {
private:
	std::string mIdentifier;
	WeakPtr<Item> mItemWeakPtr;

public:
	ItemEntry(const std::string& identifier) : mIdentifier(identifier) {};

	virtual ~ItemEntry() = default;

	virtual void registerItem() {
		short itemID = ItemRegistry::getMaxItemID() + 1;
		auto shared = SharedPtr<T>(new T(mIdentifier, itemID));
		Zenova_Info("{}: {}", mIdentifier, itemID);
		ItemRegistry::registerItem(shared);
		mItemWeakPtr = shared;
	}

	virtual void initializeClient() 
	{
		mItemWeakPtr.get()->setIcon(mIdentifier, 0);
	}

	virtual WeakPtr<Item> getCurrentWeak() 
	{
		return mItemWeakPtr;
	}
};

class ItemDefinition {
private:
	inline static std::map<std::string, SharedPtr<ItemEntryBase>> mItemMap;
	inline static std::vector<ItemGroup> mItemGroups;

	inline static void (*_registerItems)(bool);
	static void registerItems(bool enableExperimentalGameplay) 
	{
		_registerItems(enableExperimentalGameplay);

		for (auto& item : mItemMap) 
		{
			item.second->registerItem();
		}
	}

	inline static void (*_unregisterItems)();
	static void unregisterItems()
	{
		_unregisterItems();
	}

	inline static void (*_initClientData)();
	static void initClientData() 
	{
		_initClientData();

		for (auto& item : mItemMap) 
		{
			item.second->initializeClient();
		}
	}

	inline static void (*_initCreativeItems)(ActorInfoRegistry*, BlockDefinitionGroup*, bool);
	static void initCreativeItems(ActorInfoRegistry* actorReg, BlockDefinitionGroup* blockDefGroup, bool flag)
	{
		_initCreativeItems(actorReg, blockDefGroup, flag);

		for (ItemGroup& group : mItemGroups) 
		{
			Item::beginCreativeGroup(group.langKey, mItemMap[group.iconItem]->getCurrentWeak().get(), 0, nullptr);
			
			for (std::string identifier : group.itemIdentifiers)
			{
				Item* item = mItemMap[identifier]->getCurrentWeak().get();
				item->setCategory(group.category);
				Item::addCreativeItem(item, 0);
			}

			Item::endCreativeGroup();
		}
	}

public:
	static void InitializeHooks() 
	{
		Zenova_Hook(VanillaItems::registerItems, &registerItems, &_registerItems);
		Zenova_Hook(VanillaItems::unregisterItems, &unregisterItems, &_unregisterItems);
		Zenova_Hook(VanillaItems::initClientData, &initClientData, &_initClientData);
		Zenova_Hook(VanillaItems::initCreativeItemsCallback, &initCreativeItems, &_initCreativeItems);
	}

	template<typename T>
	static void RegisterItem(const std::string& identifier) 
	{
		SharedPtr<ItemEntry<T>> shared(new ItemEntry<T>(identifier));
		mItemMap[identifier] = shared;
	}

	static void CreateItemGroup(const std::string& iconItem, const std::string& langKey, CreativeItemCategory category, const std::vector<std::string>& items) 
	{
		mItemGroups.push_back({
			iconItem,
			langKey,
			category,
			items
		});
	}
};