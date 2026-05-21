#include "Shader.h"
#include "../engine/Core.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::ifstream vertexFile(vertexPath);
	std::ifstream fragmentFile(fragmentPath);

	if (!vertexFile.is_open())
	{
		std::cout << "Failed to open vertex shader file: "
			<< vertexPath << std::endl;
	}

	if (!fragmentFile.is_open())
	{
		std::cout << "Failed to open fragment shader file: "
			<< fragmentPath << std::endl;
	}

	std::stringstream vertexStream;
	std::stringstream fragmentStream;

	vertexStream << vertexFile.rdbuf();
	fragmentStream << fragmentFile.rdbuf();

	std::string vertexCode = vertexStream.str();
	std::string fragmentCode = fragmentStream.str();

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);

		std::cout << "Vertex Shader Compilation Failed:\n"
			<< infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);

		std::cout << "Fragment Shader Compilation Failed:\n"
			<< infoLog << std::endl;
	}

	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(ID, 512, nullptr, infoLog);

		std::cout << "Shader Program Linking Failed:\n"
			<< infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setVec4(const std::string& name,
	float v1,
	float v2,
	float v3,
	float v4)
{
	int location = glGetUniformLocation(ID, name.c_str());

	glUniform4f(location, v1, v2, v3, v4);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat)
{
	glUniformMatrix4fv(
		glGetUniformLocation(ID, name.c_str()),
		1,
		GL_FALSE,
		glm::value_ptr(mat)
	);
}