#pragma once
#include "../engine/Core.h"
#include "../graphics/Shader.h"

class Block
{
public:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int texture;

	Block();
	void draw(Shader& shader, glm::vec3 position);

private:

	void setupMesh();
	void loadTexture();

};