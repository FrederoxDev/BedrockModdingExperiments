#include "Zenova.h"
#include "generated/initcpp.h"
#include "ModRegistry.h"
#include "Items/TestItem.h"
#include "Items/TestItem2.h"
#include "Minecraft/Items/Item.h"
#include "Blocks/TestBlock.h"

#define CreateHook(a, b, c) \
	Zenova::Platform::CreateHook(a, b, c)

#define SlideAddress(a) \
	reinterpret_cast<void*>(Zenova::Hook::SlideAddress(a))

inline static std::string(*_testFunc)();
static std::string testFunc() {
	auto& a = _testFunc();
	Zenova_Info("Value of A: {}", a);
	return a;
}

MOD_FUNCTION void ModStart() {
	ModRegistry::InitializeHooks();
	ModRegistry::RegisterItem<TestItem>("fx:test_item");
	ModRegistry::RegisterItem<TestItem2>("fx:test_item_2");

	ModRegistry::RegisterBlock<TestBlock>("fx:test_block", MaterialType::Metal);

	ModRegistry::CreateItemGroup("fx:test_item", "itemGroup.test.name", CreativeItemCategory::Decorations, 
		{ "fx:test_item", "fx:test_item_2" }
	);
}