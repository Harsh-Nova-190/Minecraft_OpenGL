#include "Noise.h"
#include "../engine/Core.h"

float Noise::getHeight(int worldX, int worldZ)
{
	return 10.0f + sin(worldX * 0.08f) * 4.0f + cos(worldZ * 0.08f) * 4.0f;
}