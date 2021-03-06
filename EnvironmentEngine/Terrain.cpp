#include "Terrain.h"

Terrain::Terrain(int gridX, int gridZ, Texture texture, StaticLoader loader) : gridX(gridX), gridZ(gridZ)
{
	this->x = gridX * SIZE;
	this->z = gridZ * SIZE;
	this->model = generateFlatTerrain(loader, texture);
}

Terrain::~Terrain()
{
}

Model Terrain::generateFlatTerrain(StaticLoader& loader, Texture& texture)
{
	std::vector<float> vertices;
	std::vector<float> uvs;
	std::vector<float> normals;
	std::vector<int> indices;

	for (int i = 0; i<VERTEX_COUNT; i++) {
		for (int j = 0; j<VERTEX_COUNT; j++) {
			vertices.push_back((float)j / ((float)VERTEX_COUNT - 1) * SIZE);
			vertices.push_back(0);
			vertices.push_back((float)i / ((float)VERTEX_COUNT - 1) * SIZE);
			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);
			uvs.push_back((float)j / ((float)VERTEX_COUNT - 1));
			uvs.push_back((float)i / ((float)VERTEX_COUNT - 1));
		}
	}
	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices.push_back(topLeft);
			indices.push_back(bottomLeft);
			indices.push_back(topRight);
			indices.push_back(topRight);
			indices.push_back(bottomLeft);
			indices.push_back(bottomRight);
		}
	}
	Model model = loader.loadMesh(vertices, uvs, indices);
	model.setTexture(texture);
	return model;
}
