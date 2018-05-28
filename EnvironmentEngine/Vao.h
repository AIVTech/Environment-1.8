#pragma once

#include <glad\glad.h>
#include <vector>
#include <stdarg.h>

#include "Vbo.h"

class Vao
{
public:
	Vao();

	void bind();
	void unbind();
	
	// stores data in an GL_ELEMENT_ARRAY_BUFFER
	void addIndicesBuffer(std::vector<int>& indices);
	
	// stores float data in one of the attribute lists of a vao
	void addAttributef(int attribNum, int coordinateSize, std::vector<float>& data);
	// stores int data in one of the attribute lists of a vao
	void addAttributei(int attribNum, int coordinateSize, std::vector<int>& data);
	
	// enables vao attributes. requires the number of attributes, and then their indexes
	void enableAttribs(int count, ...);
	// disables vao attributes. requires the number of attributes, and then their indexes
	void disableAttribs(int count, ...);

	// get vertex count to start drawing
	int getVertexCount() { return this->vertexCount; }

	// get id of the vao
	unsigned int getID() { return this->id; }

	void remove();

	~Vao();

private:
	unsigned int id;
	int vertexCount;
	std::vector<Vbo> buffers;
	void createVao();
};

