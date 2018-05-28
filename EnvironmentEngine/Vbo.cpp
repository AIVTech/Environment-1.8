#include "Vbo.h"

Vbo::Vbo(int type)
{
	this->type = type;
	createVbo();
}

Vbo::~Vbo()
{
}

void Vbo::createVbo()
{
	glGenBuffers(1, &id);
}

void Vbo::bind()
{
	glBindBuffer(type, id);
}

void Vbo::unbind()
{
	glBindBuffer(type, 0);
}

void Vbo::remove()
{
	glDeleteBuffers(1, &id);
}

void Vbo::storeStaticData(std::vector<float> data)
{
	glBufferData(type, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
}

void Vbo::storeStaticData(std::vector<int> data)
{
	glBufferData(type, data.size() * sizeof(int), &data[0], GL_STATIC_DRAW);
}

void Vbo::storeDynamicData(std::vector<float> data)
{
	glBufferData(type, data.size() * sizeof(float), &data[0], GL_DYNAMIC_DRAW);
}

void Vbo::storeDynamicData(std::vector<int> data)
{
	glBufferData(type, data.size() * sizeof(int), &data[0], GL_DYNAMIC_DRAW);
}

