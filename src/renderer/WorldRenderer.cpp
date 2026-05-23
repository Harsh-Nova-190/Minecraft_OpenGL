#include "../engine/Core.h"
#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(BlockRenderer& blockRenderer)
	: m_BlockRenderer(blockRenderer)
{
}

void WorldRenderer::render(World& world, Shader& shader)
{
	for(int x = 0; x < World::WIDTH; x++)
	{
		for(int y = 0; y < World::HEIGHT; y++)
		{
			for(int z = 0; z < World::DEPTH; z++)
			{
				if(!world.isBlockSolid(x, y, z))
				{
					continue;
				}

				FaceFlags faces;
				faces.top = !world.isBlockSolid(x, y + 1, z);
				faces.bottom = !world.isBlockSolid(x, y - 1, z);
				faces.left = !world.isBlockSolid(x - 1, y, z);
				faces.right = !world.isBlockSolid(x + 1, y, z);
				faces.front = !world.isBlockSolid(x, y, z + 1);
				faces.back = !world.isBlockSolid(x, y, z - 1);

				if (faces.top || faces.bottom || faces.left ||
					faces.right || faces.front || faces.back)
				{
					m_BlockRenderer.drawBlock(shader,
						glm::vec3(x - World::WIDTH / 2.0f, y, z - World::DEPTH / 2.0f),
						faces);
				}
			}
		}
	}
}