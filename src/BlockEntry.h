#pragma once
#include "Minecraft/Memory/SharedPtr.h"
#include "Minecraft/Blocks/BlockTypeRegistry.h"
#include "Minecraft/Items/BlockItem.h"
#include "Minecraft/Blocks/BlockDefinitionGroup.h"
#include "Zenova.h"
#include "Minecraft/Items/ItemRegistry.h"

class BlockEntryBase {
protected:
	WeakPtr<BlockLegacy> mBlockWeakPtr;

public:
	virtual ~BlockEntryBase() = default;
    virtual void registerBlock(BlockDefinitionGroup* blockGroup) = 0;
	virtual void registerBlockItem() = 0;
	virtual WeakPtr<BlockLegacy> getCurrentWeak() = 0;
};

template <typename T>
class BlockEntry : BlockEntryBase
{
private:
	const std::string mIdentifier;
	MaterialType mMatType;

public:
	BlockEntry(const std::string &identifier, MaterialType matType) : mIdentifier(identifier), mMatType(matType) {};
	virtual ~BlockEntry() = default;

    virtual void registerBlock(BlockDefinitionGroup* blockGroup) 
    {
		Material material = Material::getMaterial(mMatType);
		SharedPtr<T> block = SharedPtr<T>::make(mIdentifier, blockGroup->getNextBlockId(), material);
		BlockTypeRegistry::mBlockLookupMap[block->getRawNameId()] = block;
		mBlockWeakPtr = BlockTypeRegistry::lookupByName(block->getRawNameId());
    }

	virtual void registerBlockItem()
	{
		ItemRegistry::registerBlockItem<BlockItem>(mBlockWeakPtr->getDescriptionId(), *mBlockWeakPtr);
	}

	virtual WeakPtr<BlockLegacy> getCurrentWeak()
	{
		return mBlockWeakPtr;
	}
};