#pragma once
#include <glm/glm.hpp>

class Camera
{
	private:

		float fov;
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;

	public:
		Camera();
		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix(float aspectRatio);
};