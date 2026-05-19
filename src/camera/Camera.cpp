#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>


Camera::Camera()
{
	fov = 60.0f;
	Position = glm::vec3(0.0f, 0.0f, 3.0f);
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
	MovementSpeed = 5.0f;
	yaw = -90.0f;
	pitch = 0.0f;
	MouseSensitivity = 0.1f;
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio)
{
	return glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
}

void Camera::moveForward(float deltaTime)
{
	Position += Front * MovementSpeed * deltaTime;
}

void Camera::moveBackward(float deltaTime)
{
	Position -= Front * MovementSpeed * deltaTime;
}

void Camera::moveLeft(float deltaTime)
{
	Position -= glm::normalize(glm::cross(Front, Up)) * MovementSpeed * deltaTime;
}

void Camera::moveRight(float deltaTime)
{
	Position += glm::normalize(glm::cross(Front, Up)) * MovementSpeed * deltaTime;
}

void Camera::updateCameraVectors()
{
	glm::vec3 direction;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	Front = glm::normalize(direction);
}

void Camera::processMouseMovement(float xoffset, float yoffset)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;
	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}
	updateCameraVectors();
}