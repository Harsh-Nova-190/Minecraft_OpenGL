#include "ChunkMeshBuilder.h"
#include "../world/Chunk.h"
#include "../world/ChunkManager.h"
#include "../world/CubeData.h"


void ChunkMeshBuilder::BuildMesh(Chunk& chunk, ChunkManager& manager)
{
	chunk.meshVertices.clear();

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
				faces.left = !manager.isBlockSolidWorld(wx - 1, wy, wz);
				faces.right = !manager.isBlockSolidWorld(wx + 1, wy, wz);
				faces.front = !manager.isBlockSolidWorld(wx, wy, wz + 1);
				faces.back = !manager.isBlockSolidWorld(wx, wy, wz - 1);
				faces.top = !manager.isBlockSolidWorld(wx, wy + 1, wz);
				faces.bottom = !manager.isBlockSolidWorld(wx, wy - 1, wz);

				glm::vec3 pos(
					x + chunk.chunkPosition.x * Chunk::SIZE,
					y + chunk.chunkPosition.y * Chunk::SIZE,
					z + chunk.chunkPosition.z * Chunk::SIZE);

				BlockType blockType = chunk.blocks[x][y][z].type;
				int sideTexture;
				int topTexture;
				int bottomTexture;

				switch (blockType)
				{
				case BlockType::Stone:
					sideTexture = 0;
					topTexture = 0;
					bottomTexture = 0;
					break;

				case BlockType::Dirt:
					sideTexture = 1;
					topTexture = 1;
					bottomTexture = 1;
					break;

				case BlockType::Grass:
					sideTexture = 2;
					topTexture = 3;
					bottomTexture = 1;
					break;

				default:
					continue;
				}

				if (faces.top || faces.bottom || faces.left ||
					faces.right || faces.front || faces.back)
				{
					if (faces.front)  AddFace(chunk, 0, pos, sideTexture);
					if (faces.back)   AddFace(chunk, 30, pos, sideTexture);
					if (faces.left)   AddFace(chunk, 60, pos, sideTexture);
					if (faces.right)  AddFace(chunk, 90, pos, sideTexture);
					if (faces.top)    AddFace(chunk, 120, pos, topTexture);
					if (faces.bottom) AddFace(chunk, 150, pos, bottomTexture);
				}
			}
		}
	}
	chunk.mesh.uploadMesh(chunk.meshVertices);
	std::cout << "Chunk: " << chunk.chunkPosition.x << ", " << chunk.chunkPosition.z << " Vertices: " << chunk.meshVertices.size() << std::endl;
	std::cout << "Verticies: " << chunk.meshVertices.size() << std::endl;
}

void ChunkMeshBuilder::AddFace(Chunk& chunk, int faceOffset, const glm::vec3& position, int tileIndex)
{
	const int atlasColumns = 4;
	const int atlasRows = 4;
	const float tileWidth = 1.0f / atlasColumns;
	const float tileHeight = 1.0f / atlasRows;

	int tileX = tileIndex % atlasColumns;
	int tileY = tileIndex / atlasColumns;

	for (int i = 0; i < 30; i += 5)
	{
		float rawU = cubeVertices[faceOffset + i + 3];
		float rawV = cubeVertices[faceOffset + i + 4];

		float u = (tileX + rawU) * tileWidth;
		float v = 1.0f - ((tileY + 1) * tileHeight) + (rawV * tileHeight);

		chunk.meshVertices.push_back(cubeVertices[faceOffset + i + 0] + position.x);
		chunk.meshVertices.push_back(cubeVertices[faceOffset + i + 1] + position.y);
		chunk.meshVertices.push_back(cubeVertices[faceOffset + i + 2] + position.z);
		chunk.meshVertices.push_back(u);
		chunk.meshVertices.push_back(v);
	}
}