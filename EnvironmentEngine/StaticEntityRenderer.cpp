#include "StaticEntityRenderer.h"

StaticEntityRenderer::StaticEntityRenderer(glm::mat4 projectionMatrix, StaticEntityShader shader)
{
	this->shader = shader;
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
}

StaticEntityRenderer::~StaticEntityRenderer()
{
}

void StaticEntityRenderer::render(std::map<int, std::vector<Entity*>>& entities)
{
	for (std::map<int, std::vector<Entity*>>::iterator iter = entities.begin(); iter != entities.end(); ++iter)
	{
		Model& model = iter->second.at(0)->getModel(); // extract the model from the first element in the list
		prepareModel(model);
		std::vector<Entity*> batch = iter->second;
		for (Entity* entity : batch)
		{
			prepareInstance(*entity);
			glDrawElements(GL_TRIANGLES, model.getVao().getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		unbindModel(model);
	}
}

void StaticEntityRenderer::prepareModel(Model& model)
{
	model.getVao().bind();
	model.getVao().enableAttribs(2, 0, 1);
	model.getTexture().bind(0);
}

void StaticEntityRenderer::prepareInstance(Entity& entity)
{
	glm::mat4 transformation = GameMath::createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
	shader.loadTransformationMatrix(transformation);
}

void StaticEntityRenderer::unbindModel(Model& model)
{
	model.getVao().disableAttribs(2, 0, 1);
	model.getVao().unbind();
}

