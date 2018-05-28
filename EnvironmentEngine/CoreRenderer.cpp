#include "CoreRenderer.h"

CoreRenderer::CoreRenderer() : staticEntityRenderer(glm::mat4(1.0), staticEntityShader)
{
	createProjectionMatrix();
	staticEntityRenderer = StaticEntityRenderer(projectionMatrix, staticEntityShader);
	glEnable(GL_DEPTH_TEST);
}

CoreRenderer::~CoreRenderer()
{
}

void CoreRenderer::prepare()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CoreRenderer::renderScene(std::vector<Entity*>& entities, FpsCamera& camera)
{
	for (Entity* entity : entities)
	{
		processEntity(entity);
	}
	render(camera);
}

void CoreRenderer::processEntity(Entity* entity)
{
	int id = entity->getModel().getModelID();
	if (entityHashMap.find(id) != entityHashMap.end()) 
	{
		// if a key exists already
		std::vector<Entity*>& batch = entityHashMap.at(id);
		batch.push_back(entity);
	}
	else
	{
		// create a new key and insert it into the map
		std::vector<Entity*> newBatch;
		newBatch.push_back(entity);
		std::pair<int, std::vector<Entity*>> newPair = std::pair<int, std::vector<Entity*>>(id, newBatch);
		entityHashMap.insert(newPair);
	}
}

void CoreRenderer::render(FpsCamera& camera)
{
	prepare();
	staticEntityShader.start();
	staticEntityShader.loadViewMatrix(camera);
	staticEntityRenderer.render(entityHashMap);
	staticEntityShader.stop();

	entityHashMap.clear();
}

void CoreRenderer::cleanUp()
{
	staticEntityRenderer.cleanUp();
}

void CoreRenderer::createProjectionMatrix()
{
	float aspectRatio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	float factor = fov / 2.0f;
	float factorResult = factor * 3.141592653589793f / 180.0f;
	float y_scale = (float)((1.0f / tanf(factorResult)) * aspectRatio);
	float x_scale = y_scale / aspectRatio;
	float frustum_length = far_plane - near_plane;

	projectionMatrix = glm::mat4(1.0);
	projectionMatrix[0][0] = x_scale;
	projectionMatrix[1][1] = y_scale;
	projectionMatrix[2][2] = -((far_plane + near_plane) / frustum_length);
	projectionMatrix[2][3] = -1;
	projectionMatrix[3][2] = -((2 * near_plane * far_plane) / frustum_length);
	projectionMatrix[3][3] = 0;
}

