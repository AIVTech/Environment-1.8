#pragma once

#include <glad\glad.h>
#include <vector>
#include "Entity.h"
#include "StaticEntityShader.h"
#include "GameMath.h"
#include <map>

class StaticEntityRenderer
{
public:
	StaticEntityRenderer(glm::mat4 projectionMatrix, StaticEntityShader shader);

	void render(std::map<int, std::vector<Entity*>>& entities);
	void cleanUp() { shader.cleanUp(); }

	~StaticEntityRenderer();
private:
	StaticEntityShader shader;

	void prepareModel(Model& model);
	void prepareInstance(Entity& entity);
	void unbindModel(Model& model);
};

