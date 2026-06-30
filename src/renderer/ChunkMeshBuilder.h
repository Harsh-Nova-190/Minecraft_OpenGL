#pragma once
#include "../engine/Core.h"

class Chunk;
class ChunkManager;


class ChunkMeshBuilder
{

public:
	void BuildMesh(Chunk& chunk, ChunkManager& manager);

private:
	void AddFace(Chunk& chunk, int faceOffset, const glm::vec3& position, int tileIndex);

};