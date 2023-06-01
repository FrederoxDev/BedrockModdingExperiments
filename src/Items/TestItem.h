#pragma once
#include "Minecraft/Items/Item.h"
#include "Minecraft/Items/ItemStackBase.h"
#include "Zenova.h"

class Level;

class TestItem : public Item {
public:
	TestItem(const std::string&, short);

	virtual int getAttackDamage() const {
		return 200;
	}

	virtual void appendFormattedHovertext(const ItemStackBase& itemStackBase, Level& level, std::string& hoverText, const bool param_2) const {
		Zenova_Info("{}", itemStackBase.getItem().get()->getRawNameId());
	};
};