#pragma once

#include "../world/World.h"
#include "../graphics/Shader.h"
#include "../camera/Camera.h"

class WorldRenderer
{
public:

	WorldRenderer();
	
	void render(World& world, const Camera& camera);

	int renderedBlockCount;
	unsigned int AtlasTexture;

private:
	Shader m_Shader;

	unsigned int loadTexture(const char* path);
};