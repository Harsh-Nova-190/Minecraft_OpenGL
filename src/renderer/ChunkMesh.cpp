#include "ChunkMesh.h"

ChunkMesh::ChunkMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

void ChunkMesh::uploadMesh(const std::vector<float>& vertices)
{
	vertexCount = static_cast<int>(vertices.size() / 5);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void ChunkMesh::draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}