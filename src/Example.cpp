#include "Zenova.h"
#include "generated/initcpp.h"
#include "Items/TestItem.h"
#include "ModRegistry.h"

MOD_FUNCTION void ModStart() {
	ModRegistry::InitializeHooks();
	ModRegistry::RegisterItem<TestItem>("test_item");

	ModRegistry::CreateItemGroup("test_item", "itemGroup.test.name", CreativeItemCategory::Items, 
		{ "test_item" }
	);
}