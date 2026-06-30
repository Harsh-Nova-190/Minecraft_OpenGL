#pragma once
#include "../engine/Core.h"

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
		glm::vec3 getPosition() const;
		glm::mat4 getViewMatrix() const;
		glm::mat4 getProjectionMatrix(float aspectRatio) const;
		void moveForward(float deltaTime);
		void moveBackward(float deltaTime);
		void moveLeft(float deltaTime);
		void moveRight(float deltaTime);
		void processMouseMovement(float xoffset, float yoffset);
		void processKeyboardInput(GLFWwindow* window, float deltaTime);
		//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};