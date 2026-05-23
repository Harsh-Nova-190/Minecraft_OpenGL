#pragma once

#include "../engine/Core.h"

class Shader
{
public:
	unsigned int ID;
	bool wireframeMode = false;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setVec4(const std::string& name,
		float v1,
		float v2,
		float v3,
		float v4);
	
	void setMat4(const std::string& name,
				const glm::mat4& mat);

	void keyBoardInput(GLFWwindow* window);
};