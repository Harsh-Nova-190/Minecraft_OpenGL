#pragma once

#include "../world/World.h"
#include "../graphics/Shader.h"
#include "../camera/Camera.h"
#include "BlockRenderer.h"

class WorldRenderer
{
public:

	WorldRenderer(BlockRenderer& blockRenderer);
	
	void render(World& world, const Camera& camera);

private:
	BlockRenderer& m_BlockRenderer;
	Shader m_Shader;
};