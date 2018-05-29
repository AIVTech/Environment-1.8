#include "TerrainRenderer.h"

TerrainRenderer::TerrainRenderer(glm::mat4 projectionMatrix, TerrainShader shader)
{
	this->shader = shader;
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
}

TerrainRenderer::~TerrainRenderer()
{
}

void TerrainRenderer::render(std::vector<Terrain*>& terrains)
{
	for (Terrain* terrain : terrains)
	{
		prepareTerrain(*terrain);
		loadTransformationMatrix(*terrain);
		glDrawElements(GL_TRIANGLES, terrain->getModel().getVao().getVertexCount(), GL_UNSIGNED_INT, 0);
		unbindModel(*terrain);
	}
}

void TerrainRenderer::prepareTerrain(Terrain& terrain)
{
	Model& model = terrain.getModel();
	model.getVao().bind();
	model.getVao().enableAttribs(2, 0, 1);
	model.getTexture().bind(0);
}

void TerrainRenderer::loadTransformationMatrix(Terrain& terrain)
{
	glm::vec3 position = glm::vec3(terrain.getPosX(), 0, terrain.getPosZ());
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	float scale = 1;
	glm::mat4 transformation = GameMath::createTransformationMatrix(position, rotation, scale);
	shader.loadTransformationMatrix(transformation);
}

void TerrainRenderer::unbindModel(Terrain& terrain)
{
	Model& model = terrain.getModel();
	model.getVao().disableAttribs(2, 0, 1);
	model.getVao().unbind();
}
