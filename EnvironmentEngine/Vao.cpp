#include "Vao.h"

Vao::Vao()
{
	createVao();
}

Vao::~Vao()
{

}

void Vao::createVao()
{
	glGenVertexArrays(1, &id);
}

void Vao::bind()
{
	glBindVertexArray(id);
}

void Vao::unbind()
{
	glBindVertexArray(0);
}

void Vao::remove()
{
	for (Vbo vbo : buffers)
	{
		vbo.remove();
	}
	glDeleteVertexArrays(1, &id);
}

void Vao::addIndicesBuffer(std::vector<int>& indices)
{
	vertexCount = indices.size();
	Vbo indexBuffer = Vbo(GL_ELEMENT_ARRAY_BUFFER);
	indexBuffer.bind();
	indexBuffer.storeStaticData(indices);
}

void Vao::addAttributef(int attribNum, int coordinateSize, std::vector<float>& data)
{
	Vbo vbo = Vbo(GL_ARRAY_BUFFER);
	vbo.bind();
	vbo.storeStaticData(data);
	glVertexAttribPointer(attribNum, coordinateSize, GL_FLOAT, false, 0, (void*)0);
	vbo.unbind();
	buffers.push_back(vbo);
}

void Vao::addAttributei(int attribNum, int coordinateSize, std::vector<int>& data)
{
	Vbo vbo = Vbo(GL_ARRAY_BUFFER);
	vbo.bind();
	vbo.storeStaticData(data);
	glVertexAttribIPointer(attribNum, coordinateSize, GL_INT, 0, (void*)0);
	vbo.unbind();
	buffers.push_back(vbo);
}

void Vao::enableAttribs(int count, ...)
{
	va_list arguments;
	va_start(arguments, count);
	for (int i = 0; i < count; i++)
	{
		int attrib = va_arg(arguments, int);
		glEnableVertexAttribArray(attrib);
	}
	va_end(arguments);
}

void Vao::disableAttribs(int count, ...)
{
	va_list arguments;
	va_start(arguments, count);
	for (int i = 0; i < count; i++)
	{
		int attrib = va_arg(arguments, int);
		glDisableVertexAttribArray(attrib);
	}
	va_end(arguments);
}
