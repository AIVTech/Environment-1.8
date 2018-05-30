#include "World.h"

World::World(StaticLoader& loader) : models(loader)
{
	init(loader);
}

World::~World()
{
}

void World::init(StaticLoader& loader)
{
	loadEntities(loader);
	loadTerrains(loader);
}

void World::loadEntities(StaticLoader& loader)
{
	for (int i = 0; i < 6; i++)
	{
		Entity* crate = new Entity(models.cube, glm::vec3(110.0f + i * 3, 0.5f, 105.0f), glm::vec3(0.f, 0.f, 0.f), 1.f);
		entities.push_back(crate);
	}

	Entity* stall = new Entity(models.stall, glm::vec3(120.0f, 0.0f, 120.0f), glm::vec3(0, 0, 0), 0.6f);
	entities.push_back(stall);
}

void World::loadTerrains(StaticLoader& loader)
{
	Terrain* terrain = new Terrain(0, 0, loader.loadTexture("darkGrass.jpg"), loader);
	Terrain* terrain2 = new Terrain(1, 0, loader.loadTexture("darkGrass.jpg"), loader);
	terrains.push_back(terrain);
	terrains.push_back(terrain2);
}
