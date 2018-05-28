#pragma once

#include "StaticEntityRenderer.h"
#include "DisplayManager.h"

class CoreRenderer
{
public:
	CoreRenderer();

	void prepare();
	void renderScene(std::vector<Entity*>& entities, FpsCamera& camera);
	void cleanUp();

	~CoreRenderer();

private:
	StaticEntityRenderer staticEntityRenderer;
	StaticEntityShader staticEntityShader;

	std::map<int, std::vector<Entity*>> entityHashMap;
	void processEntity(Entity* entity, FpsCamera& camera);
	void render(FpsCamera& camera);

	glm::mat4 projectionMatrix;
	float fov = 60;
	float near_plane = 0.1f;
	float far_plane = 4000.0f;
	float farViewDistance = 100.0f;
	void createProjectionMatrix();

	// entity processing methods
	bool shouldRenderEntity(Entity& entity, FpsCamera& camera);
	bool isEntityInFrustum(Entity& entity, FpsCamera& camera);
	bool isEntityInRange(Entity& entity, FpsCamera& camera);
};

