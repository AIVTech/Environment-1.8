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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -2.0f);

	int width, height, nrChannels;

	std::string filepath = std::string(ASSETS_FOLDER);
	filepath.append(TEXTURES_FOLDER);
	filepath.append(filename);

	unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		textureID = 0;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	Texture texture = Texture(textureID);
	if (textureID != 0) textures.push_back(texture);
	return texture;
}


