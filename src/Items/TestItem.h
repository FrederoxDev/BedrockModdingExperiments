#pragma once
#include "Minecraft/Items/Item.h"
#include "Minecraft/Items/ItemStackBase.h"
#include "Zenova.h"
#include "Minecraft/NBT/CompoundTag.h"
#include <stdlib.h>

class Level;

class TestItem : public Item {
protected:
	int mPrefix;

public:
	TestItem(const std::string&, short);

	virtual void readAdditionalData(ItemStackBase& itemStackBase, const CompoundTag& compound) const 
	{
		Item::readAdditionalData(itemStackBase, compound);
		Zenova_Info("Item: {}", itemStackBase.getItem()->getCommandName());
		//Zenova_Info("Compound: {}", compound.toString());
	}

	//virtual int getAttackDamage() const {
	//	return 200;
	//}

	//virtual void appendFormattedHovertext(const ItemStackBase& itemStackBase, Level& level, std::string& hoverText, const bool param_2) const {
	//	CompoundTag* data = itemStackBase.mUserData.get();

	//	// Crashes when trying to set data in the creative item menu
	//	if (!data->contains("prefix")) {
	//		int id = rand();
	//		// Write temp data
	//		Zenova_Info("id: {}", id, id % 20);
	//		data->putInt("prefix", id % 20);
	//		itemStackBase.save();
	//	}

	//	int prefix = data->getInt("prefix");

	//	Item::appendFormattedHovertext(itemStackBase, level, hoverText, param_2);
	//	hoverText = std::to_string(prefix) + hoverText;
	//};
};