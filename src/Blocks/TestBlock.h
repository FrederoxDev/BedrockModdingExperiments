#pragma once
#include "Minecraft/Blocks/BlockLegacy.h"

class TestBlock : public BlockLegacy {
public:
	TestBlock(const std::string& identifier, int id, Material material);
};