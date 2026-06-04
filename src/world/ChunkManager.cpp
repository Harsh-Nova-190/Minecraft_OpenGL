#include "ChunkManager.h"

ChunkManager::ChunkManager()
{
	createInitialChunks();
}

std::vector<Chunk>& ChunkManager::getChunks()
{
	return chunks;
}

void ChunkManager::createInitialChunks()
{
    for (int x = -2; x <= 2; x++)
    {
        for (int z = -2; z <= 2; z++)
        {
            chunks.emplace_back(x, 0, z);
        }
    }
}

bool ChunkManager::isBlockSolidWorld(int worldX, int worldY, int worldZ)
{
	int chunkX = (int)floor(worldX / (float)Chunk::SIZE);
	int chunkY = (int)floor(worldY / (float)Chunk::SIZE);
	int chunkZ = (int)floor(worldZ / (float)Chunk::SIZE);

    for (auto& chunk : chunks)
    {
        if (chunk.chunkPosition.x == chunkX && chunk.chunkPosition.y == chunkY && chunk.chunkPosition.z == chunkZ)
        {
            int localX = worldX - chunkX * Chunk::SIZE;
			int localY = worldY - chunkY * Chunk::SIZE;
            int localZ = worldZ - chunkZ * Chunk::SIZE;
			return chunk.isBlockSolid(localX, localY, localZ);
        }
    }
    return false;
}

void ChunkManager::update(const glm::vec3& playerPosition)
{
    int playerChunkX = static_cast<int>(floor(playerPosition.x / (float)Chunk::SIZE));
    int playerChunkZ = static_cast<int>(floor(playerPosition.z / (float)Chunk::SIZE));

    if (playerChunkX != currentChunkX || playerChunkZ != currentChunkZ)
    {
		currentChunkX = playerChunkX;
		currentChunkZ = playerChunkZ;

        loadChunksAroundPlayer();
    }
}

void ChunkManager::loadChunksAroundPlayer()
{
	chunks.clear();

    for (int x = currentChunkX - RENDER_DISTANCE; x <= currentChunkX + RENDER_DISTANCE; x++)
    {
        for (int z = currentChunkZ - RENDER_DISTANCE; z <= currentChunkZ + RENDER_DISTANCE; z++)
        {
            chunks.emplace_back(x, 0, z);
        }
    }
}