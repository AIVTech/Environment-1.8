#pragma once

#include "Vao.h"
#include "Texture.h"
#include "AABB.h"

class Model
{
public:
	Model() : texture(0) {}
	Model(Vao vao) : texture(0) { this->vao = vao; }
	Model(Vao vao, Texture texture) : texture(0) { this->vao = vao; this->texture = texture; }

	Vao& getVao() { return vao; }

	void setTexture(Texture texture) { this->texture = texture; }
	Texture& getTexture() { return this->texture; }

	float xMin, xMax, yMin, yMax, zMin, zMax;

	void setModelID(int id) { this->modelID = id; }
	int getModelID() { return this->modelID; }

	~Model() {}

private:
	Vao vao;
	Texture texture;
	int modelID;
};