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
    for (int x = 0; x <= 0; x++)
    {
        for (int z = 0; z <= 0; z++)
        {
            chunks.emplace_back(x, 0, z);
        }
    }
}