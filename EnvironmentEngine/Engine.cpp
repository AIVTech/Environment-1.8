#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <glad\glad.h>
#include <GLFW\glfw3.h>

// Local Includes
#include "DisplayManager.h"
#include "StaticLoader.h"
#include "CoreRenderer.h"
#include "ModelManager.h"

void ProcessInput(GLFWwindow* window);

int main()
{
	DisplayManager display;
	display.CreateDisplay(1920, 1080, "Environment 1.8", false);

	StaticLoader loader;
	CoreRenderer renderer;
	ModelManager models(loader);
	std::vector<Entity*> entities;

	Entity crate = Entity(models.cube, glm::vec3(0.0f, 1.4f, -5.0f), glm::vec3(0.f, 0.f, 0.f), 1.f);
	entities.push_back(&crate);

	for (int i = 0; i < 10; i++)
	{
		float xPos = (float)(rand() % 5 - 5), yPos = (float)(rand() % 3 - 1), zPos = (float)(rand() % 100 - 50);
		float scale = (float)(rand() % 1) - 0.4f;
		Entity* cube = new Entity(models.cube, glm::vec3(xPos, yPos, zPos), glm::vec3(0, 0, 0), scale);
		entities.push_back(cube);
	}

	Entity stall = Entity(models.stall, glm::vec3(10.0f, -0.4f, -20.0f), glm::vec3(0, 0, 0), 0.4f);
	entities.push_back(&stall);

	FpsCamera camera = FpsCamera(&display);

	while (!display.WindowShouldClose())
	{
		// logic
		camera.update();

		// rendering
		renderer.renderScene(entities, camera);

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
