#pragma once

#include "StaticEntityRenderer.h"
#include "TerrainRenderer.h"
#include "DisplayManager.h"
#include "CollisionDetectionManager.h"

class CoreRenderer
{
public:
	CoreRenderer();

	void prepare();
	void renderScene(std::vector<Entity*>& entities, std::vector<Terrain*>& terrains, FpsCamera& camera, Player& player);
	void cleanUp();

	~CoreRenderer();

private:
	StaticEntityRenderer staticEntityRenderer;
	StaticEntityShader staticEntityShader;

	TerrainRenderer terrainRenderer;
	TerrainShader terrainShader;

	CollisionDetectionManager collisionDetector;

	std::map<int, std::vector<Entity*>> entityHashMap;
	void processEntity(Entity* entity, FpsCamera& camera);
	void render(FpsCamera& camera, std::vector<Terrain*>& terrains);

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
	void performPlayerCollisionDetection(Player& player, Entity& entity);
};

