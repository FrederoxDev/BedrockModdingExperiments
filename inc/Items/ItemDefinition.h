#pragma once
#include <map>
#include <string>
#include "Util/SharedPtr.h"
#include "Items/ItemRegistry.h"
#include "Items/VanillaItems.h"

struct ItemEntryTexture {
	std::string mName;
	int mAux;
};

class ItemEntryBase {
protected:
	WeakPtr<Item> currentWeak;
public:
	virtual ~ItemEntryBase() = default;
	virtual void registerItem() = 0;
	virtual void unregisterItem() = 0;
	virtual ItemEntryBase& setIcon(const std::string&, int) = 0;
	virtual void initializeClientData() = 0;
	virtual WeakPtr<Item> getCurrentWeak() const = 0;
	virtual ItemEntryBase& createCreativeGroup(const std::string&, short, const CompoundTag*) { return *this; }
	virtual ItemEntryBase& addCreativeItem(short) { return *this; }
	virtual ItemEntryBase& finishCreativeGroup() { return *this; }
};

template<typename T, typename... Args>
class ItemEntry : ItemEntryBase {
    T* ptr = nullptr;
	ItemEntryTexture mItemEntryTexture;
public:
	ItemEntry(const std::string& nameId, short numId, Args&&... args) {
		ptr = new T(nameId, numId, std::forward<Args>(args)...);
	}

	virtual ~ItemEntry() = default;

	virtual void registerItem() {
		auto shared = SharedPtr<T>(ptr);
		ItemRegistry::registerItem(shared);
		currentWeak = shared;
	}

	virtual void unregisterItem() {
		
	}

    virtual ItemEntryBase& setIcon(const std::string& name, int aux) {
		mItemEntryTexture = { name, aux };
		return *this;
	}

	virtual void initializeClientData() {
		currentWeak->setIcon(mItemEntryTexture.mName, mItemEntryTexture.mAux);
	}

	virtual WeakPtr<Item> getCurrentWeak() const {
		return currentWeak;
	}
};

class ItemDefinition {
public:
	inline static std::map<std::string, SharedPtr<ItemEntryBase>> mItemDefinitionGroup;

	inline static void (*_registerItems)(bool);
	static void registerItems(bool enableExperimentalGameplay) {
		_registerItems(enableExperimentalGameplay);
		for (auto& defGroup : mItemDefinitionGroup)
			defGroup.second->registerItem();
	}

	inline static void (*_unregisterItems)();
	static void unregisterItems() {
		_unregisterItems();
		for (auto& defGroup : mItemDefinitionGroup)
			defGroup.second->unregisterItem();
	}

	inline static void (*_initClientData)();
	static void initClientData() {
		_initClientData();
		for (auto& defGroup : mItemDefinitionGroup)
			defGroup.second->initializeClientData();
	}

	static void Initialize() {
		Zenova_Hook(VanillaItems::registerItems, &registerItems, &_registerItems);
		Zenova_Hook(VanillaItems::unregisterItems, &unregisterItems, &_unregisterItems);
		Zenova_Hook(VanillaItems::initClientData, &initClientData, &_initClientData);
	}

	template<typename T, typename... Args>
	static WeakPtr<ItemEntry<T, Args&&...>> addItem(const std::string& identifier, short numId, Args&&... args) {
		if (numId < 0)
			numId = ItemRegistry::getMaxItemID() + 256;
		auto shared = SharedPtr<ItemEntry<T, Args&&...>>(new ItemEntry<T, Args&&...>(identifier, numId, std::forward<Args>(args)...));
		mItemDefinitionGroup[identifier] = shared;
		return shared;
	}//lets set a icon? kk icon identifier is ok, in 
};