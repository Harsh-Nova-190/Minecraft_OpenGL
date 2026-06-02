#pragma once
#include <vector>
#include "Chunk.h"

class ChunkManager
{
public:
	ChunkManager();

	std::vector<Chunk>& getChunks();

private:
	std::vector<Chunk> chunks;
	void createInitialChunks();
};