#include "FpsCamera.h"

FpsCamera::FpsCamera(DisplayManager* display)
{
	this->display = display;
}

void FpsCamera::update()
{
	processKeyboardInput();
	processMouseInput();
}

void FpsCamera::processKeyboardInput()
{
	float velocity = movementSpeed * display->GetFrameTimeSeconds();

	if (glfwGetKey(display->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		this->position.x += glm::sin(glm::radians(yaw)) * velocity;
		this->position.z -= glm::cos(glm::radians(yaw)) * velocity;
	}
	if (glfwGetKey(display->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		this->position.x -= glm::sin(glm::radians(yaw)) * velocity;
		this->position.z += glm::cos(glm::radians(yaw)) * velocity;
	}
	if (glfwGetKey(display->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		this->position.x += glm::sin(glm::radians(yaw - 90)) * velocity;
		this->position.z -= glm::cos(glm::radians(yaw - 90)) * velocity;
	}
	if (glfwGetKey(display->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		this->position.x -= glm::sin(glm::radians(yaw - 90)) * velocity;
		this->position.z += glm::cos(glm::radians(yaw - 90)) * velocity;
	}
}

void FpsCamera::processMouseInput()
{
	float xOffset = (float)display->GetDX() * mouseSensitivity;
	float yOffset = (float)display->GetDY() * mouseSensitivity;

	yaw += (float)xOffset;
	pitch += (float)-yOffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
}

