#include "StaticLoader.h"

StaticLoader::StaticLoader()
{
}

StaticLoader::~StaticLoader()
{
}

Model StaticLoader::loadMesh(std::vector<float> vertices, std::vector<float> textureCoordinates, std::vector<int> indices)
{
	Vao vao;
	vaos.push_back(vao);
	vao.bind();
	vao.addIndicesBuffer(indices);
	vao.addAttributef(0, 3, vertices);
	vao.addAttributef(1, 2, textureCoordinates);
	vao.unbind();
 	return Model(vao);
}

void StaticLoader::cleanUp()
{
	for (Vao vao : vaos)
	{
		vao.remove();
	}
	for (Texture texture : textures)
	{
		texture.remove();
	}
}

Texture StaticLoader::loadTexture(const char* filename)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	std::string filepath = std::string(ASSETS_FOLDER);
	filepath.append(TEXTURES_FOLDER);
	filepath.append(filename);
	unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.2f);
	}
	else
	{
		// Failed to Load Texture
	}
	stbi_image_free(data);
	textures.push_back(textureID);
	return textureID;
}


