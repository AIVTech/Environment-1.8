#include "FpsCamera.h"

FpsCamera::FpsCamera(Player* player, DisplayManager* display)
{
	this->player = player;
	this->display = display;
	this->yaw -= 180;
	this->pitch += 20;
}

void FpsCamera::update()
{
	processKeyboardInput();
	processMouseInput();
	calculateCameraPositionAroundPlayer();

	this->upwardSpeed += gravity * display->GetFrameTimeSeconds();
	player->increasePosition(0, upwardSpeed * display->GetFrameTimeSeconds(), 0);
	if (player->getPosition().y < 0.5f)
	{
		inAir = false;
		upwardSpeed = 0;
		player->getPosition().y = 0.5f;
	}
}

void FpsCamera::jump()
{
	if (!inAir)
	{
		inAir = true;
		this->upwardSpeed = jump_power;
	}
}

void FpsCamera::processKeyboardInput()
{
	float velocity = movementSpeed * display->GetFrameTimeSeconds();

	if (glfwGetKey(display->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		this->position.x += glm::sin(glm::radians(yaw)) * velocity;
		this->position.z -= glm::cos(glm::radians(yaw)) * velocity;

		this->player->increasePosition(glm::sin(glm::radians(yaw)) * velocity, 0, 0);
		this->player->increasePosition(0, 0, -glm::cos(glm::radians(yaw)) * velocity);
	}
	if (glfwGetKey(display->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		this->position.x -= glm::sin(glm::radians(yaw)) * velocity;
		this->position.z += glm::cos(glm::radians(yaw)) * velocity;

		this->player->increasePosition(-glm::sin(glm::radians(yaw)) * velocity, 0, 0);
		this->player->increasePosition(0, 0, glm::cos(glm::radians(yaw)) * velocity);
	}
	if (glfwGetKey(display->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		this->position.x += glm::sin(glm::radians(yaw - 90)) * velocity;
		this->position.z -= glm::cos(glm::radians(yaw - 90)) * velocity;
		
		this->player->increasePosition(glm::sin(glm::radians(yaw - 90)) * velocity, 0, 0);
		this->player->increasePosition(0, 0, -glm::cos(glm::radians(yaw - 90)) * velocity);
	}
	if (glfwGetKey(display->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		this->position.x -= glm::sin(glm::radians(yaw - 90)) * velocity;
		this->position.z += glm::cos(glm::radians(yaw - 90)) * velocity;

		this->player->increasePosition(-glm::sin(glm::radians(yaw - 90)) * velocity, 0, 0);
		this->player->increasePosition(0, 0, glm::cos(glm::radians(yaw - 90)) * velocity);
	}
	if (glfwGetKey(display->GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		jump();
	}
}

void FpsCamera::processMouseInput()
{
	float xOffset = (float)display->GetDX() * mouseSensitivity;
	float yOffset = (float)display->GetDY() * mouseSensitivity;

	yaw += (float)xOffset;
	pitch += (float)-yOffset;

	player->getRotation().y -= (float)xOffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
}

glm::vec3 FpsCamera::getFrontVector()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
	return front;
}


void FpsCamera::calculateCameraPositionAroundPlayer()
{
	float offsetX = (float)(distanceFromPlayer * glm::sin(glm::radians(player->getRotation().y)));
	float offsetZ = (float)(distanceFromPlayer * glm::cos(glm::radians(player->getRotation().y)));
	float verticalDistance = distanceFromPlayer * glm::sin(glm::radians(pitch+6));

	position.x = player->getPosition().x - offsetX;
	position.z = player->getPosition().z - offsetZ;
	position.y = player->getPosition().y + verticalDistance;
}
