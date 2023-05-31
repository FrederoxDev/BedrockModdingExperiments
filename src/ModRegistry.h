#pragma once
#include <map>
#include <vector>
#include "Minecraft/Items/Item.h"
#include "Minecraft/Memory/SharedPtr.h"
#include "Minecraft/Items/VanillaItems.h"
#include "Minecraft/Items/ItemRegistry.h"
#include "BlockEntry.h"
#include "ItemEntry.h"
#include "Minecraft/Blocks/BlockDefinitionGroup.h"

enum RegistryEntryType {
	ItemEntryType,
	BlockEntryType
};

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
	inline static std::map<std::string, RegistryEntryType> mEntryTypeLookup;
	inline static std::map<std::string, SharedPtr<ItemEntryBase>> mItemMap;
	inline static std::map<std::string, SharedPtr<BlockEntryBase>> mBlockMap;
	inline static std::vector<ItemGroup> mItemGroups;

	inline static void (*_registerItems)(bool);
	static void registerItems(bool enableExperimentalGameplay)
	{
		_registerItems(enableExperimentalGameplay);

		for (auto& item : mItemMap)
		{
			item.second->registerItem();
		}

		for (auto& block : mBlockMap)
		{
			block.second->registerBlockItem();
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
			// Todo: Support block as icon
			Item::beginCreativeGroup(group.langKey, mItemMap[group.iconItem]->getCurrentWeak().get(), 0, nullptr);

			for (const std::string identifier : group.itemIdentifiers)
			{
				addCreativeItem(identifier, group.category);
			}

			Item::endCreativeGroup();
		}
	}

	static void addCreativeItem(const std::string identifier, CreativeItemCategory category) 
	{
		RegistryEntryType entryType = mEntryTypeLookup[identifier];

		if (entryType == RegistryEntryType::ItemEntryType)
		{
			Item* item = mItemMap[identifier]->getCurrentWeak().get();
			item->setCategory(category);
			Item::addCreativeItem(item, 0);
		}

		else if (entryType == RegistryEntryType::BlockEntryType)
		{
			BlockLegacy* block = mBlockMap[identifier]->getCurrentWeak().get();
			//block->setCategory(category);
			Item::addCreativeItem(block->getDefaultState());
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
		mEntryTypeLookup[identifier] = RegistryEntryType::ItemEntryType;
		mItemMap[identifier] = shared;
	}

	template <typename T>
	static void RegisterBlock(const std::string &identifier, MaterialType matType)
	{
		SharedPtr<BlockEntry<T>> shared(new BlockEntry<T>(identifier, matType));
		mEntryTypeLookup[identifier] = RegistryEntryType::BlockEntryType;
		mBlockMap[identifier] = shared;
	}

	static void CreateItemGroup(const std::string &iconItem, const std::string &langKey, CreativeItemCategory category, const std::vector<std::string> &items)
	{
		mItemGroups.push_back({iconItem, langKey, category, items});
	}
};