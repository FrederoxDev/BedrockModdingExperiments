#include "TestItem.h"

TestItem::TestItem(const std::string& identifier, short id) : Item(identifier, id) {
	setCategory(CreativeItemCategory::Items);
};