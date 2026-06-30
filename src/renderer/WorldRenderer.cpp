#include "WorldRenderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

unsigned int WorldRenderer::loadTexture(const char* path)
{
	unsigned int tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture: " << path << std::endl;
	}
	stbi_image_free(data);
	return tex;
}

WorldRenderer::WorldRenderer()
	: m_Shader("shaders/triangle.vert", "shaders/triangle.frag")
{
	AtlasTexture = loadTexture("textures/texture_atlas.png");
}

void WorldRenderer::render(World& world, const Camera& camera)
{
	renderedBlockCount = 0;
	m_Shader.use();
	m_Shader.setMat4("view", camera.getViewMatrix());
	m_Shader.setMat4("projection", camera.getProjectionMatrix(1280.0f / 720.0f));
	m_Shader.setInt("texture1", 0);
	m_Shader.keyBoardInput(glfwGetCurrentContext());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, AtlasTexture);
	
	for (auto& chunk : world.chunkManager.getChunks())
	{
		chunk.mesh.draw();
		renderedBlockCount++;
	}
}