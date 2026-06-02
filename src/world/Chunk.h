#pragma once
#include "Block.h"
#include "../engine/Core.h"

struct ChunkCoord
{
	int x, y, z;
	
	bool operator == (const ChunkCoord& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}
};

class Chunk
{
public:
	static constexpr int SIZE = 1;

	Block blocks[SIZE][SIZE][SIZE];

	glm::ivec3 chunkPosition;

	Chunk(int chunkX, int chunkY, int chunkZ);

	bool isBlockSolid(int x, int y, int z);

private:
	void generateFlatTerrain();
};