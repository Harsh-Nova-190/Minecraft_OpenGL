#pragma once
#include "../engine/Core.h"
#include "../graphics/Shader.h"
#include "../world/Block.h"

struct FaceFlags
{
	bool front, back, left, right, top, bottom;
};

class BlockRenderer
{
public:
	BlockRenderer();
	void initialize();

	void drawBlock(Shader& shader, glm::vec3 position, FaceFlags faces, BlockType type);

private:
	unsigned int VAO, VBO;
	unsigned int textures[4];
	unsigned int grassTopTexture;

	void loadTextures();
	unsigned int loadSingleTexture(const char* path);
};