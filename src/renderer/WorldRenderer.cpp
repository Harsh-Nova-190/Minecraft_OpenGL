#include "../engine/Core.h"
#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(BlockRenderer& blockRenderer)
	: m_BlockRenderer(blockRenderer)
{
}

void WorldRenderer::render(World& world, Shader& shader)
{
	for (auto& chunk : world.chunkManager.getChunks())
	{

		for (int x = 0; x < Chunk::SIZE; x++)
		{
			for (int y = 0; y < Chunk::SIZE; y++)
			{
				for (int z = 0; z < Chunk::SIZE; z++)
				{
					if (!chunk.isBlockSolid(x, y, z))
					{
						continue;
					}

					FaceFlags faces;
					faces.top = !chunk.isBlockSolid(x, y + 1, z);
					faces.bottom = !chunk.isBlockSolid(x, y - 1, z);
					faces.left = !chunk.isBlockSolid(x - 1, y, z);
					faces.right = !chunk.isBlockSolid(x + 1, y, z);
					faces.front = !chunk.isBlockSolid(x, y, z + 1);
					faces.back = !chunk.isBlockSolid(x, y, z - 1);

					if (faces.top || faces.bottom || faces.left ||
						faces.right || faces.front || faces.back)
					{
						BlockType type = chunk.blocks[x][y][z].type;
						glm::vec3 worldPos = glm::vec3(
							chunk.chunkPosition.x * Chunk::SIZE + x,
							chunk.chunkPosition.y * Chunk::SIZE + y,
							chunk.chunkPosition.z * Chunk::SIZE + z
						);
						m_BlockRenderer.drawBlock(shader, worldPos, faces, type);
					}
				}

			}
		}
	}
}