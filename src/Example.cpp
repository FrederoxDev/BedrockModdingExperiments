#include "Zenova.h"
#include "generated/initcpp.h"
#include "ItemDefinition.h"
#include "Items/TestItem.h"
#include "Items/TestItem2.h"
#include "Minecraft/Items/Item.h"

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

inline static void(*_test)();
static void test() {
	Zenova_Info("Sup!");
	_test();
}

MOD_FUNCTION void ModStart() {
	/*CreateHook(SlideAddress(0x318c60), &test, &_test);*/

	ItemDefinition::InitializeHooks();
	ItemDefinition::RegisterItem<TestItem>("fx:test_item");
	ItemDefinition::RegisterItem<TestItem2>("fx:test_item_2");

	ItemDefinition::CreateItemGroup("fx:test_item", "itemGroup.test.name", CreativeItemCategory::Decorations, 
		{ "fx:test_item", "fx:test_item_2" }
	);
}