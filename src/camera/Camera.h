#pragma once
#include <glm/glm.hpp>

class Camera
{
	private:

		// camera POV
		float fov;
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;

		// Movement setting 
		float MovementSpeed;
		
		// Mouse Setting
		float yaw;
		float pitch;

		float MouseSensitivity;

		void updateCameraVectors();

	public:
		Camera();
		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix(float aspectRatio);
		void moveForward(float deltaTime);
		void moveBackward(float deltaTime);
		void moveLeft(float deltaTime);
		void moveRight(float deltaTime);
		void processMouseMovement(float xoffset, float yoffset);
};