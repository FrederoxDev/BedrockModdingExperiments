#pragma once
#include <map>
#include <vector>
#include "Minecraft/Items/Item.h"
#include "Minecraft/Util/SharedPtr.h"
#include "Minecraft/Items/VanillaItems.h"
#include "Minecraft/Items/ItemRegistry.h"
#include "BlockEntry.h"
#include "ItemEntry.h"
#include "Minecraft/Blocks/BlockDefinitionGroup.h"

struct ItemGroup
{
	const std::string iconItem;
	const std::string langKey;
	CreativeItemCategory category;
	const std::vector<std::string> itemIdentifiers;
};

class ModRegistry
{
private:
	inline static std::map<std::string, SharedPtr<ItemEntryBase>> mItemMap;
	inline static std::map<std::string, SharedPtr<BlockEntryBase>> mBlockMap;
	inline static std::vector<ItemGroup> mItemGroups;

	inline static void (*_registerItems)(bool);
	static void registerItems(bool enableExperimentalGameplay)
	{
		_registerItems(enableExperimentalGameplay);

		for (auto &item : mItemMap)
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

		for (auto &item : mItemMap)
		{
			item.second->initializeClient();
		}
	}

	inline static void (*_initCreativeItems)(ActorInfoRegistry *, BlockDefinitionGroup *, bool);
	static void initCreativeItems(ActorInfoRegistry *actorReg, BlockDefinitionGroup *blockDefGroup, bool flag)
	{
		_initCreativeItems(actorReg, blockDefGroup, flag);

		for (ItemGroup &group : mItemGroups)
		{
			Item::beginCreativeGroup(group.langKey, mItemMap[group.iconItem]->getCurrentWeak().get(), 0, nullptr);

			for (std::string identifier : group.itemIdentifiers)
			{
				Item *item = mItemMap[identifier]->getCurrentWeak().get();
				item->setCategory(group.category);
				Item::addCreativeItem(item, 0);
			}

			Item::endCreativeGroup();
		}
	}

	inline static void (*_registerBlocks)(BlockDefinitionGroup*);
	static void registerBlocks(BlockDefinitionGroup* defGroup) 
	{
		_registerBlocks(defGroup);

		for (auto &block : mBlockMap)
		{
			block.second->registerBlock(defGroup);
		}
	}

public:
	static void InitializeHooks()
	{
		Zenova_Hook(VanillaItems::registerItems, &registerItems, &_registerItems);
		Zenova_Hook(VanillaItems::unregisterItems, &unregisterItems, &_unregisterItems);
		Zenova_Hook(VanillaItems::initClientData, &initClientData, &_initClientData);
		Zenova_Hook(VanillaItems::initCreativeItemsCallback, &initCreativeItems, &_initCreativeItems);
		Zenova_Hook(BlockDefinitionGroup::registerBlocks, &registerBlocks, &_registerBlocks);
	}

	template <typename T>
	static void RegisterItem(const std::string &identifier)
	{
		SharedPtr<ItemEntry<T>> shared(new ItemEntry<T>(identifier));
		mItemMap[identifier] = shared;
	}

	template <typename T>
	static void RegisterBlock(const std::string &identifier, MaterialType matType)
	{
		SharedPtr<BlockEntry<T>> shared(new BlockEntry<T>(identifier, matType));
		mBlockMap[identifier] = shared;
	}

	static void CreateItemGroup(const std::string &iconItem, const std::string &langKey, CreativeItemCategory category, const std::vector<std::string> &items)
	{
		mItemGroups.push_back({iconItem, langKey, category, items});
	}
};