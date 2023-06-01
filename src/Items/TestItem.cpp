#include "TestItem.h"

TestItem::TestItem(const std::string& identifier, short id) : Item(identifier, id) {
	setMaxStackSize(1);
	setMaxDamage(200);
};