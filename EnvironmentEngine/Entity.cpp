#include "Entity.h"

Entity::Entity(Model model, glm::vec3 position, glm::vec3 rotation, float scale) : model(model)
{
	this->model = model;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;

	// Setting the bounding box
	AABB* boundingBox = new AABB;
	boundingBox->xMin = model.xMin;
	boundingBox->xMax = model.xMax;

	boundingBox->yMin = model.yMin;
	boundingBox->yMax = model.yMax;

	boundingBox->zMin = model.zMin;
	boundingBox->zMax = model.zMax;

	AABB::setWorldPosition(boundingBox, position);

	this->boundingBox = *boundingBox;
}

Entity::~Entity()
{
}



