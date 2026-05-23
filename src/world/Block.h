#pragma once

enum class BlockType
{
	Air = 0,
	Grass,
	Dirt,
	Stone
};

struct Block
{
	BlockType type;
};