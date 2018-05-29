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
	std::vector<Terrain*> terrains;

	Entity crate = Entity(models.cube, glm::vec3(110.0f, 0.5f, 105.0f), glm::vec3(0.f, 0.f, 0.f), 0.4f);
	entities.push_back(&crate);

	Entity stall = Entity(models.stall, glm::vec3(120.0f, 0.0f, 120.0f), glm::vec3(0, 0, 0), 0.5f);
	entities.push_back(&stall);

	Terrain terrain = Terrain(0, 0, loader.loadTexture("darkGrass.jpg"), loader);
	Terrain terrain2 = Terrain(1, 0, loader.loadTexture("darkGrass.jpg"), loader);
	terrains.push_back(&terrain);
	terrains.push_back(&terrain2);

	FpsCamera camera = FpsCamera(&display);

	while (!display.WindowShouldClose())
	{
		// logic
		camera.update();

		// rendering
		renderer.renderScene(entities, terrains, camera);

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
