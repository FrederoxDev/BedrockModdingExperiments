#include "Zenova.h"
#include "generated/initcpp.h"
#include "Items/ItemDefinition.h"
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
	ItemDefinition::Initialize();
	ItemDefinition::addItem<TestItem>("fx:test_item", -1)->setIcon("fx:test_item", 0);
}
