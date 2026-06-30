#pragma once
#include "../../engine/Core.h"

class TextureAtlas
{
public:
	static constexpr int ATLAS_SIZE = 64;
	static constexpr int TILE_SIZE = 16;

	static glm::vec2 getUVMin(int tileIndex);
	static glm::vec2 getUVMax(int tileIndex);

private:

};