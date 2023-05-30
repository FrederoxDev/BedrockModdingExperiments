#pragma once
#include "Minecraft/Util/SharedPtr.h"

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
