#include <glad\glad.h>
#include "DisplayManager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

DisplayManager::DisplayManager()
{
}

DisplayManager::~DisplayManager()
{
}

bool DisplayManager::CreateDisplay(int width, int height, const char* title, bool fullscreen)
{
	this->screen_width = width;
	this->screen_height = height;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (fullscreen) 
	{
		window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
	}
	if (window == NULL)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(0);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}
}

bool DisplayManager::WindowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void DisplayManager::Update()
{
	// Mouse Input
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	xoffset = (float)xpos - lastX;
	yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top

	lastX = (float)xpos;
	lastY = (float)ypos;

	// Per-frame timing
	float currentFrame = (float)glfwGetTime();
	this->deltaTime = (currentFrame - lastFrame)*100.0f;
	lastFrame = currentFrame;

	glfwSwapBuffers(window);
	glfwPollEvents();
}

float DisplayManager::GetFrameTimeSeconds()
{
	return deltaTime;
}

void DisplayManager::Destroy()
{
	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
