#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(BlockRenderer& blockRenderer)
	: m_BlockRenderer(blockRenderer), m_Shader("shaders/triangle.vert", "shaders/triangle.frag")
{
}

void WorldRenderer::render(World& world, const Camera& camera)
{
	m_Shader.use();
	m_Shader.setMat4("view", camera.getViewMatrix());
	m_Shader.setMat4("projection", camera.getProjectionMatrix(1280.0f / 720.0f));
	m_Shader.keyBoardInput(glfwGetCurrentContext());
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

					int wx = chunk.chunkPosition.x * Chunk::SIZE + x;
					int wy = chunk.chunkPosition.y * Chunk::SIZE + y;
					int wz = chunk.chunkPosition.z * Chunk::SIZE + z;

					FaceFlags faces;
					faces.top = !world.chunkManager.isBlockSolidWorld(wx, wy + 1, wz);
					faces.bottom = !world.chunkManager.isBlockSolidWorld(wx, wy - 1, wz);
					faces.left = !world.chunkManager.isBlockSolidWorld(wx - 1, wy, wz);
					faces.right = !world.chunkManager.isBlockSolidWorld(wx + 1, wy, wz);
					faces.front = !world.chunkManager.isBlockSolidWorld(wx, wy, wz + 1);
					faces.back = !world.chunkManager.isBlockSolidWorld(wx, wy, wz - 1);

					if (faces.top || faces.bottom || faces.left ||
						faces.right || faces.front || faces.back)
					{
						m_BlockRenderer.drawBlock(m_Shader, glm::vec3(wx, wy, wz), faces, chunk.blocks[x][y][z].type);
					}
				}

			}
		}
	}
}