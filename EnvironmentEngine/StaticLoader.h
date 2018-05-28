#pragma once

#include "Model.h"
#include "stb_image.h"
#include <string>

#define ASSETS_FOLDER "Assets/"
#define MODEL_FOLDER "Models/"
#define TEXTURES_FOLDER "Textures/"

class StaticLoader
{
public:
	StaticLoader();

	Model loadMesh(std::vector<float> vertices, std::vector<float> textureCoordinates, std::vector<int> indices);
	Texture loadTexture(const char* filename);

	void cleanUp();

	~StaticLoader();
private:
	std::vector<Vao> vaos;
	std::vector<Texture> textures;
};

