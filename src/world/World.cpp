#include "World.h"

World::World()
{
	generateFlatTerrain();
}

void World::generateFlatTerrain()
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int z = 0; z < DEPTH; z++)
		{
			for (int y = 0; y < HEIGHT; y++)
			{
				if (y == 0)
				{
					blocks[x][y][z].type = BlockType::Grass;
				}
				else
				{
					blocks[x][y][z].type = BlockType::Air;
				}
			}
		}
	}
}

bool World::isBlockSolid(int x, int y, int z)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || z < 0 || z >= DEPTH)
	{
		return false;
	}
	return blocks[x][y][z].type != BlockType::Air;
}