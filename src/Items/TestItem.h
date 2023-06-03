#pragma once
#include "Minecraft/Items/Item.h"
#include "Minecraft/Items/ItemStackBase.h"
#include "Zenova.h"
#include "Minecraft/NBT/CompoundTag.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include "Minecraft/Util/ColorFormat.h"

class Level;

enum SwordPrefix {
	Broken,
	Shoddy,
	Common,
	Fine,
	Superior,
	UnknownPrefix,
};

inline int GetRandomInt(int minInclusive, int maxInclusive) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(minInclusive, maxInclusive);
	return dis(gen);
};

inline SwordPrefix getRandomPrefix() {
	std::vector<SwordPrefix> prefixes = { Broken, Shoddy, Common, Fine, Superior };
	std::vector<int> weights = { 3, 15, 40, 8, 3 };
	std::vector<SwordPrefix> evaluated;
	int totalWeight = 0;

	for (int i = 0; i < prefixes.size(); ++i) {
		totalWeight += weights[i];

		for (int j = 0; j < weights[i]; ++j) {
			evaluated.push_back(prefixes[i]);
		}
	}

	int index = GetRandomInt(0, totalWeight - 1);
	return evaluated[index];
};

inline std::string prefixToString(SwordPrefix prefix) {
	if (prefix == Broken)             return ColorFormat::DarkGrey + "[Broken]";
	else if (prefix == Shoddy)        return ColorFormat::Grey + "[Shoddy]";
	else if (prefix == Common)        return ColorFormat::White + "[Common]";
	else if (prefix == Fine)          return ColorFormat::Blue + "[Fine]";
	else if (prefix == Superior)      return ColorFormat::Yellow + "[Superior]";
	else return "[Unknown]";
}

struct TestItemData {
	SwordPrefix mPrefix;

	TestItemData() {}
	TestItemData(SwordPrefix prefix) : mPrefix(prefix) {};

	CompoundTag parse() {
		CompoundTag tag = CompoundTag();
		tag.putInt("mPrefix", mPrefix);
		return tag;
	}

	void writeToCompound(CompoundTag& tag) const {
		tag.putInt("mPrefix", (int)mPrefix);
	}

	void readFromCompound(const CompoundTag* tag) {
		if (tag != nullptr) {
			if (tag->contains("mPrefix")) {
				mPrefix = (SwordPrefix)tag->getInt("mPrefix");
			}
			else {
				mPrefix = getRandomPrefix();
			}
		}
	}
};

class TestItem : public Item {
private:
	mutable std::map<const ItemStackBase*, TestItemData> mItemReferences;

public:
	TestItem(const std::string&, short);

	virtual void saveAdditionalData(const ItemStackBase& base, CompoundTag& tag) const 
	{
		auto& item = mItemReferences.find(&base);

		if (item != mItemReferences.end()) {
			item->second.writeToCompound(tag);
		}
		else {
			TestItemData data = TestItemData();
			data.writeToCompound(tag);
			mItemReferences[&base] = data;
		}
	}

	virtual void readAdditionalData(ItemStackBase& base, const CompoundTag& constTag) const 
	{
		auto& item = mItemReferences.find(&base);
		if (item != mItemReferences.end()) {
			item->second.readFromCompound(&constTag);
		}
		else {
			TestItemData data = TestItemData();
			data.readFromCompound(&constTag);
			mItemReferences[&base] = data;
		}
	}

	virtual void appendFormattedHovertext(const ItemStackBase& base, Level& level, std::string& hoverText, const bool showCategory) const 
	{
		if (mItemReferences.find(&base) == mItemReferences.end()) {
			createNew(const_cast<ItemStackBase&>(base));
		}
		auto& item = mItemReferences.find(&base);
		hoverText = prefixToString(item->second.mPrefix) + ColorFormat::Reset + " Test Item";
		hoverText += "\n" + std::to_string(item->second.mPrefix + 3) + " Damage";
	}

	void createNew(ItemStackBase& base) const
	{
		TestItemData data = TestItemData();
		CompoundTag* tag = base.mUserData.get();

		if (tag != nullptr) {
			data.readFromCompound(tag);
			mItemReferences[&base] = data;
			base.setMaxDamage(data.mPrefix);
		}
	}
};