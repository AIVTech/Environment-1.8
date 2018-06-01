#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player(Model model, glm::vec3 position, glm::vec3 rotation, float scale) :
		Entity(model, position, rotation, scale)
	{

	}

private:
	Model model;
	glm::vec3 position;
	glm::vec3 rotation;
	float scale;
};