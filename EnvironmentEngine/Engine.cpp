//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <glad\glad.h>
#include <GLFW\glfw3.h>

// Local Includes
#include "DisplayManager.h"
#include "StaticLoader.h"
#include "CoreRenderer.h"
#include "World.h"
#include "Player.h"

void ProcessInput(GLFWwindow* window);

int main()
{
	DisplayManager display;
	display.CreateDisplay(800, 600, "Environment 1.8", false);

	StaticLoader loader;
	CoreRenderer renderer;
	World world(loader);

	Player* player = new Player(world.getModels().cube, glm::vec3(100, 0.5f, 105), glm::vec3(0, 0, 0), 1);
	world.getEntities().push_back(player);

	FpsCamera camera = FpsCamera(player, &display);

	while (!display.WindowShouldClose())
	{
		// logic
		camera.update();

		// rendering
		renderer.renderScene(world.getEntities(), world.getTerrains(), camera, *player);

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
