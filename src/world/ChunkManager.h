#pragma once
#include <vector>
#include <algorithm>
#include "Chunk.h"
#include "../renderer/ChunkMeshBuilder.h"

class ChunkManager
{
public:
	static constexpr int RENDER_DISTANCE = 4;

	int currentChunkX = 0;
	int currentChunkZ = 0;

	ChunkManager();

	std::vector<Chunk>& getChunks();
	bool isBlockSolidWorld(int worldX, int worldY, int worldZ);
	bool chunkExists(int chunkX, int chunkY, int chunkZ);
	void update(const glm::vec3& playerPosition);

private:
	std::vector<Chunk> chunks;
	void createInitialChunks();
	void loadChunksAroundPlayer();
	void unloadDistantChunks();
	ChunkMeshBuilder meshBuilder;
};