#pragma once

#include "ModelManager.h"
#include "StaticLoader.h"
#include "Entity.h"
#include "Terrain.h"

class World
{
public:
	World(StaticLoader& loader);

	std::vector<Entity*>& getEntities() { return entities; }
	std::vector<Terrain*>& getTerrains() { return terrains; }

	ModelManager& getModels() { return this->models; }

	~World();

private:
	ModelManager models;
	std::vector<Entity*> entities;
	std::vector<Terrain*> terrains;

	void init(StaticLoader& loader);
	void loadEntities(StaticLoader& loader);
	void loadTerrains(StaticLoader& loader);
};

