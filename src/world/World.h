#pragma once
#include "Block.h"

class World
{
public:

	static const int WIDTH = 20;
	static const int HEIGHT = 5;
	static const int DEPTH = 20;

	Block blocks[WIDTH][HEIGHT][DEPTH];

	World();

	bool isBlockSolid(int x, int y, int z);

private:
	void generateFlatTerrain();

};