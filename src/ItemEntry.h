#pragma once
#include "Minecraft/Memory/SharedPtr.h"
#include "Minecraft/Items/Item.h"

class ItemEntryBase {
protected:
	WeakPtr<Item> mItemWeakPtr;

public:
	virtual ~ItemEntryBase() = default;
	virtual void registerItem() = 0;
	virtual void initializeClient() = 0;
	virtual WeakPtr<Item> getCurrentWeak() = 0;
};

template <typename T>
class ItemEntry : ItemEntryBase {
public:
	std::string mIdentifier;
	ItemEntry(const std::string &identifier) : mIdentifier(identifier){};

	virtual ~ItemEntry() = default;

	virtual void registerItem()
	{
		mItemWeakPtr = SharedPtr<T>(new T(mIdentifier, ItemRegistry::getMaxItemID() + 1));
		ItemRegistry::registerItem(mItemWeakPtr.get());
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
