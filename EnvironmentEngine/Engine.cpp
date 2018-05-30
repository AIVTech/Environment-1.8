#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <glad\glad.h>
#include <GLFW\glfw3.h>

// Local Includes
#include "DisplayManager.h"
#include "StaticLoader.h"
#include "CoreRenderer.h"
#include "World.h"

void ProcessInput(GLFWwindow* window);

int main()
{
	DisplayManager display;
	display.CreateDisplay(1920, 1080, "Environment 1.8", false);

	StaticLoader loader;
	CoreRenderer renderer;
	World world(loader);

	FpsCamera camera = FpsCamera(&display);

	while (!display.WindowShouldClose())
	{
		// logic
		camera.update();

		// rendering
		renderer.renderScene(world.getEntities(), world.getTerrains(), camera);

		// update display
		ProcessInput(display.GetWindow());
		display.Update();
	}

	// clean up
	loader.cleanUp();
	renderer.cleanUp();
	display.Destroy();

	return 0;
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
