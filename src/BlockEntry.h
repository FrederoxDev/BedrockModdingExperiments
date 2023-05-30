#pragma once
#include "Minecraft/Memory/SharedPtr.h"
#include "Minecraft/Blocks/BlockTypeRegistry.h"
#include "Minecraft/Items/BlockItem.h"

class BlockItem;

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
	std::string mIdentifier;
	MaterialType mMatType;

public:
	BlockEntry(const std::string &identifier, MaterialType matType) : mIdentifier(identifier), mMatType(matType) {};
	virtual ~BlockEntry() = default;

    virtual void registerBlock(BlockDefinitionGroup* blockGroup) 
    {
		int id = blockGroup->getNextBlockId();
		auto shared = SharedPtr<T>(new T(mIdentifier, id, Material::getMaterial(mMatType)));
		Zenova_Info("{}", shared->getRawNameId());
		Zenova_Info("{}: {}", mIdentifier, id);
		BlockTypeRegistry::mBlockLookupMap[mIdentifier] = shared;
		//mBlockWeakPtr = shared->createWeakPtr();
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