#pragma once
#include "helper/Block.h"
#include "../engine/Core.h"
#include "../world/helper/FaceFlags.h"
#include "../renderer/ChunkMesh.h"
#include "CubeData.h"

class ChunkManager;

struct ChunkCoord
{
	int x, y, z;
	
	bool operator == (const ChunkCoord& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}
};

struct VisibleBlock
{
	glm::ivec3 position;
	BlockType type;
	FaceFlags faces;
};

class Chunk
{
public:
	static constexpr int SIZE = 6;
	Block blocks[SIZE][SIZE][SIZE];
	glm::ivec3 chunkPosition;
	Chunk(int chunkX, int chunkY, int chunkZ);
	bool isBlockSolid(int x, int y, int z);
	std::vector<VisibleBlock> visibleBlocks;
	std::vector<float> meshVertices;

	ChunkMesh mesh;

private:
	void generateTerrain();
};