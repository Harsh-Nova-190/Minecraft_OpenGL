#include "Chunk.h"


Chunk::Chunk(int chunkX, int chunkY, int chunkZ)
{
	chunkPosition = glm::ivec3(chunkX, chunkY, chunkZ);
	generateTerrain();
}

void Chunk::generateTerrain()
{
	for (int x = 0; x < SIZE; x++)
	{
		for (int z = 0; z < SIZE; z++)
		{
			for (int y = 0; y < SIZE; y++)
			{
				if (y == 0)
				{
					blocks[x][y][z].type = BlockType::Stone;
				}
				else if (y == 1 || y == 2)
				{
					blocks[x][y][z].type = BlockType::Dirt;
				}
				else if (y == 3)
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

bool Chunk::isBlockSolid(int x, int y, int z)
{
	if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || z < 0 || z >= SIZE)
	{
		return false;
	}
	return blocks[x][y][z].type != BlockType::Air;
}