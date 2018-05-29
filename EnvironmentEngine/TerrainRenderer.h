#pragma once

#include <glad\glad.h>
#include <vector>
#include "Terrain.h"
#include "TerrainShader.h"
#include "GameMath.h"
#include <map>

class TerrainRenderer
{
public:
	TerrainRenderer(glm::mat4 projectionMatrix, TerrainShader shader);

	void render(std::vector<Terrain*>& terrains);
	void cleanUp() { shader.cleanUp(); }

	~TerrainRenderer();

private:
	TerrainShader shader;

	void prepareTerrain(Terrain& terrain);
	void loadTransformationMatrix(Terrain& terrain);
	void unbindModel(Terrain& terrain);
};

