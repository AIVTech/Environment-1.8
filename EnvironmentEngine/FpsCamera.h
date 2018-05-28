#ifndef CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>
#include "DisplayManager.h"

class FpsCamera
{
public:
	FpsCamera(DisplayManager* display);

	glm::vec3 getPosition() { return this->position; }
	float getYaw() { return this->yaw; }
	float getPitch() { return this->pitch; }
	float getRoll() { return this->roll; }

	void update();

private:
	DisplayManager* display;

	void processKeyboardInput();
	void processMouseInput();

	glm::vec3 position = glm::vec3(0, 1, 0);
	float yaw, pitch, roll;

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