#ifndef TERRAIN_H
#define TERRAIN_H

#include "StaticLoader.h"

class Terrain
{
public:
	Terrain(int gridX, int gridZ, Texture texture, StaticLoader loader);

	Model& getModel() { return this->model; }
	float& getPosX() { return this->x; }
	float& getPosZ() { return this->z; }

	~Terrain();

private:
	float x, z;
	int gridX, gridZ;
	const float SIZE = 800;
	const int VERTEX_COUNT = 512;
	Model model;
	Model generateFlatTerrain(StaticLoader& loader, Texture& texture);
};

#endif // !TERRAIN_H