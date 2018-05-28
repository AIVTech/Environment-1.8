#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Model.h"

class Entity
{
public:
	Entity(Model model, glm::vec3 position, glm::vec3 rotation, float scale);

	// getters
	Model& getModel() { return this->model; }
	glm::vec3& getPosition() { return this->position; }
	glm::vec3& getRotation() { return this->rotation; }
	float& getScale() { return this->scale; }

	// setters
	void setModel(Model& model) { this->model = model; }
	void setPosition(glm::vec3& pos) { this->position = pos; }
	void setRotation(glm::vec3& rot) { this->rotation = rot; }
	void setScale(float& scale) { this->scale = scale; }

	// changing spacial parameters
	void increasePosition(float dx, float dy, float dz) { this->position.x += dx; this->position.y += dy; this->position.z += dz; }
	void increaseRotation(float dx, float dy, float dz) { this->rotation.x += dx; this->rotation.y += dy; this->rotation.z += dz; }

	~Entity();
private:
	Model model;
	glm::vec3 position;
	glm::vec3 rotation;
	float scale;
};

