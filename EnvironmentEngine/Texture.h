#pragma once

#include <glad\glad.h>

class Texture
{
public:
	Texture(unsigned int id) { this->id = id; }

	// bind the texture to an OpenGL texture unit when rendering
	void bind(int textureUnit) 
	{
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEXTURE_2D, id);
	}

	// deallocate OpenGL resources for this texture
	void remove()
	{
		glDeleteTextures(1, &id);
	}

private:
	unsigned int id;
};