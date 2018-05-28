#pragma once

#include <GLFW\glfw3.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

class DisplayManager
{
public:
	DisplayManager();

	bool CreateDisplay(int width, int height, const char* title, bool fullscreen);
	void Update();
	void Destroy();
	bool WindowShouldClose();

	GLFWwindow* GetWindow() { return this->window; }
	int GetScreenWidth() { return this->screen_width; }
	int GetScreenHeight() { return this->screen_height; }

	double GetDX() { return this->xoffset; }
	double GetDY() { return this->yoffset; }

	float GetFrameTimeSeconds();

	~DisplayManager();
private:
	GLFWwindow* window;
	int screen_width = 0;
	int screen_height = 0;

	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	// mouse position
	float lastX = screen_width / 2.0f;
	float lastY = screen_height / 2.0f;
	bool firstMouse = true;
	double xoffset = 0, yoffset = 0;
};

