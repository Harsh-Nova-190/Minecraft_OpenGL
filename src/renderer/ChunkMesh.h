#pragma once
#include "../engine/Core.h"

class ChunkMesh
{
public:
	ChunkMesh();
	void uploadMesh(const std::vector<float>& vertices);

	void draw();

private:
	unsigned int VAO = 0;
	unsigned int VBO = 0;

	int vertexCount = 0;
};