#pragma once
#include "Minecraft/Util/SharedPtr.h"
#include "Minecraft/Blocks/BlockTypeRegistry.h"

class BlockEntryBase {
protected:
	WeakPtr<BlockLegacy> mBlockWeakPtr;

public:
	virtual ~BlockEntryBase() = default;
    virtual void registerBlock(BlockDefinitionGroup* blockGroup) = 0;
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
		BlockTypeRegistry::mBlockLookupMap[mIdentifier] = shared;
		//mBlockWeakPtr = shared->createWeakPtr();
		Zenova_Info("{}: {}", mIdentifier, id);
    }

	virtual WeakPtr<BlockLegacy> getCurrentWeak()
	{
		return mBlockWeakPtr;
	}
};