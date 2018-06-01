#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Model.h"

class Entity
{
public:
	Entity(Model model, glm::vec3 position, glm::vec3 rotation, float scale);

	// Physical Properties
	bool movable = true;

	// getters
	Model& getModel() { return this->model; }
	glm::vec3& getPosition() { return this->position; }
	glm::vec3& getLastPosition() { return this->lastPosition; }
	glm::vec3& getRotation() { return this->rotation; }
	float& getScale() { return this->scale; }

	void setBoundingBox(AABB& box) { this->boundingBox = box; }
	AABB& getBoundingBox() { return this->boundingBox; }

	// setters
	void setModel(Model& model) { this->model = model; }
	void setPosition(glm::vec3& pos)
	{ 
		this->lastPosition = position; 
		this->position = pos;
		AABB::setWorldPosition(&boundingBox, pos); 
	}
	void setLastPosition(glm::vec3& pos) { this->lastPosition = pos; }
	void setRotation(glm::vec3& rot) { this->rotation = rot; }
	void setScale(float& scale) { this->scale = scale; }

	// changing spacial parameters
	void increasePosition(float dx, float dy, float dz)
	{
		this->position.x += dx; this->position.y += dy; 
		this->position.z += dz; 
		AABB::setWorldPosition(&boundingBox, position); 
	}
	void increaseRotation(float dx, float dy, float dz) { this->rotation.x += dx; this->rotation.y += dy; this->rotation.z += dz; }

	~Entity();
private:
	Model model;
	AABB boundingBox;
	glm::vec3 position;
	glm::vec3 rotation;
	float scale;
	glm::vec3 lastPosition = glm::vec3(0, 0, 0);
};

