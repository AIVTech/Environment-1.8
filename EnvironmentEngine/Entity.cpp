#include "Entity.h"

Entity::Entity(Model model, glm::vec3 position, glm::vec3 rotation, float scale) : model(model)
{
	this->model = model;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

Entity::~Entity()
{
}



