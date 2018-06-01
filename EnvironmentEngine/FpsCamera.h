#ifndef CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>
#include "Player.h"
#include "DisplayManager.h"

class FpsCamera
{
public:
	FpsCamera(Player* player, DisplayManager* display);

	glm::vec3& getPosition() { return this->position; }
	float& getYaw() { return this->yaw; }
	float& getPitch() { return this->pitch; }
	float& getRoll() { return this->roll; }

	void setPosition(glm::vec3& position) { this->position = position; }

	Player* getPlayerEntity() { return this->player; }
	void setPlayerEntity(Player* player) { this->player = player; }

	glm::vec3 getFrontVector();

	void update();

private:
	DisplayManager* display;
	Player* player;

	void processKeyboardInput();
	void processMouseInput();
	void calculateCameraPositionAroundPlayer();

	glm::vec3 position = glm::vec3(100, 15, 95);
	float yaw, pitch, roll;
	float distanceFromPlayer = 8;

	float gravity = -0.005f;
	float jump_power = 0.12f;
	float upwardSpeed = 0;
	bool inAir = false;
	void jump();

	// movement variables
	float walkingSpeed = 0.06f;
	float runningSpeed = 40;
	float crouchDistance = 4.2f;
	float movementSpeed = walkingSpeed;

	// mouse movement variables
	float mouseSensitivity = 0.02f;
	float xoffset = 0, yoffset = 0;
};

#endif // !CAMERA_H