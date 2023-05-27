#include "Zenova.h"
#include "generated/initcpp.h"
#include "ItemDefinition.h"
#include "Items/TestItem.h"
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
	ItemDefinition::InitializeHooks();
	ItemDefinition::addItem<TestItem>("fx:test_item")->setIcon("fx:test_item", 0);
}
