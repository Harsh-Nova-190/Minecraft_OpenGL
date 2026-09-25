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
			int worldX = chunkPosition.x * SIZE + x;
			int worldZ = chunkPosition.z * SIZE + z;

			int terrainHeight = Noise::getHeight(worldX, worldZ);

			for (int y = 0; y < SIZE; y++)
			{
				int worldY = chunkPosition.y * SIZE + y;
				if (worldY > terrainHeight)
				{
					blocks[x][y][z].type = BlockType::Air;
				}
				else if (worldY == terrainHeight)
				{
					blocks[x][y][z].type = BlockType::Grass;
				}
				else if (worldY >= terrainHeight - 2)
				{
					blocks[x][y][z].type = BlockType::Dirt;
				}
				else
				{
					blocks[x][y][z].type = BlockType::Stone;
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