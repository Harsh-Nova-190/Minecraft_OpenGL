#pragma once
#include "../engine/Core.h"
#include "../graphics/Shader.h"

struct FaceFlags
{
	bool front, back, left, right, top, bottom;
};

class BlockRenderer
{
public:
	BlockRenderer();
	void initialize();

	void drawBlock(Shader& shader, glm::vec3 position, FaceFlags faces);
	void loadTexture();

private:
	unsigned int VAO, VBO;
	unsigned int texture;
};