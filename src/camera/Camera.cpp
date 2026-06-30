#include "Camera.h"

extern Camera camera;

float lastX = 640.0f;
float lastY = 360.0f;
bool firstMouse = true;

Camera::Camera()
{
	fov = 60.0f;
	Position = glm::vec3(0.0f, 5.0f, 3.0f);
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
	MovementSpeed = 5.0f;
	yaw = -90.0f;
	pitch = 0.0f;
	MouseSensitivity = 0.1f;
}

glm::vec3 Camera::getPosition() const
{
	return Position;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const
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

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	camera.processMouseMovement(xoffset, yoffset);
}

void Camera::processKeyboardInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		moveForward(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		moveBackward(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		moveLeft(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		moveRight(deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}