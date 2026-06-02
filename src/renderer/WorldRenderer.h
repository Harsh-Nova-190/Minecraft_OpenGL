#pragma once

#include "../world/World.h"
#include "../graphics/Shader.h"
#include "BlockRenderer.h"

class WorldRenderer
{
public:

	WorldRenderer(BlockRenderer& blockRenderer);
	
	void render(World& world, Shader& shader);

private:
	BlockRenderer& m_BlockRenderer;
};