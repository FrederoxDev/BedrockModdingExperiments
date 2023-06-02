#pragma once
#include "Minecraft/Items/Item.h"
#include "Minecraft/Items/ItemStackBase.h"
#include "Zenova.h"
#include "Minecraft/NBT/CompoundTag.h"
#include <cstdlib>
#include <ctime>
#include <random>

class Level;

class TestItem : public Item {
public:
	TestItem(const std::string&, short);

	virtual void writeUserData(const ItemStackBase& itemStack, IDataOutput& dataOutput) const {
		CompoundTag* compound = itemStack.mUserData.get();

		if (compound != nullptr) {
			Zenova_Info("Write: {}", compound->toString());

			if (!compound->contains("prefix")) {
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<int> dist(0, 99);
				int id = dist(gen);

				//compound->putInt("prefix", id);
				Zenova_Info("Write: {}", id);
			}
			else {
				Zenova_Info("Write found: {}", compound->getInt("prefix"));
			}
		}

		Item::writeUserData(itemStack, dataOutput);
	};

	virtual void appendFormattedHovertext(const ItemStackBase& itemStack, Level& level, std::string& hoverText, const bool flag) const {
		CompoundTag* compound = itemStack.mUserData.get();
		int id = -1;

		if (compound != nullptr) {
			Zenova_Info("Append: {}", compound->toString());

			if (compound->contains("prefix")) {
				Zenova_Info("Append Read: {}", compound->getInt("prefix"));
				id = compound->getInt("prefix");
			}
			else {
				Zenova_Info("Append could not read prefix");
			}
		}

		Item::appendFormattedHovertext(itemStack, level, hoverText, flag);
		hoverText = "[" + std::to_string(id) + "] " + hoverText;
	};
};