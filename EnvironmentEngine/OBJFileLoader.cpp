#include "OBJFileLoader.h"

OBJFileLoader::OBJFileLoader()
{
}

OBJFileLoader::~OBJFileLoader()
{
}

Model OBJFileLoader::loadObjModel(const char* modelPath, const char* texturePath, StaticLoader loader)
{
	std::string fullFilepath = ASSETS_FOLDER;
	fullFilepath.append(MODEL_FOLDER);
	fullFilepath.append(modelPath);
	fullFilepath.append(OBJ_FILE_EXTENSION);
	modelPath = fullFilepath.c_str();

	std::ifstream objFile;
	objFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	float* uvsArray = new float[1];
	float* normalsArray = new float[1];

	std::vector<float> out_vertices;
	std::vector<float> out_uvs;
	std::vector<float> out_normals;
	std::vector<int> indices;

	bool firstTimeAllocation = true;

	try
	{
		objFile.open(modelPath);

		// parsing vertex data
		for (std::string line; getline(objFile, line);)
		{
			// splitting the line at whitespace
			std::istringstream iss(line);
			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
				std::istream_iterator<std::string>{} };

			if (line.find("v ") != std::string::npos)
			{
				glm::vec3 vertex;
				vertex.x = std::stof(tokens.at(1));
				vertex.y = std::stof(tokens.at(2));
				vertex.z = std::stof(tokens.at(3));
				vertices.push_back(vertex);
			}

			if (line.find("vt ") != std::string::npos)
			{
				glm::vec2 vertex;
				vertex.x = std::stof(tokens.at(1));
				vertex.y = std::stof(tokens.at(2));
				uvs.push_back(vertex);
			}

			if (line.find("vn ") != std::string::npos)
			{
				glm::vec3 vertex;
				vertex.x = std::stof(tokens.at(1));
				vertex.y = std::stof(tokens.at(2));
				vertex.z = std::stof(tokens.at(3));
				normals.push_back(vertex);
			}

			if (line.find("f ") != std::string::npos)
			{
				if (firstTimeAllocation)
				{
					firstTimeAllocation = false;
					uvsArray = new float[vertices.size() * 2];
					normalsArray = new float[vertices.size() * 3];
				}

				// parsing faces
				std::string face1 = tokens.at(1);
				std::string face2 = tokens.at(2);
				std::string face3 = tokens.at(3);

				std::vector<std::string> vertex1 = lineSplit(face1, "/");
				std::vector<std::string> vertex2 = lineSplit(face2, "/");
				std::vector<std::string> vertex3 = lineSplit(face3, "/");

				processVertex(vertex1, indices, uvs, normals, uvsArray, normalsArray);
				processVertex(vertex2, indices, uvs, normals, uvsArray, normalsArray);
				processVertex(vertex3, indices, uvs, normals, uvsArray, normalsArray);
			}
		}
		objFile.close();
	}
	catch (std::ifstream::failure e)
	{ }

	// convert list of 3d vectors into a list of floats for vertices
	for (glm::vec3 vertex : vertices)
	{
		out_vertices.push_back(vertex.x);
		out_vertices.push_back(vertex.y);
		out_vertices.push_back(vertex.z);
	}

	// convert textureCoords array to a vector
	out_uvs.insert(out_uvs.end(), &uvsArray[0], &uvsArray[vertices.size() * 2]);

	// convert normals array to a vector
	out_uvs.insert(out_uvs.end(), &normalsArray[0], &normalsArray[vertices.size() * 3]);

	Model model = loader.loadMesh(out_vertices, out_uvs, indices);
	Texture texture = loader.loadTexture(texturePath);
	model.setTexture(texture);

	// deallocate resources
	delete uvsArray;
	delete normalsArray;

	return model;
}

void OBJFileLoader::processVertex(std::vector<std::string>& vertexData, std::vector<int>& out_indices, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals,
	float* uvsArray, float* normalsArray)
{
	int vertexPointer = std::stoi(vertexData.at(0)) - 1;
	out_indices.push_back(vertexPointer);
	glm::vec2 currentUV = uvs.at(std::stoi(vertexData.at(1))-1);
	glm::vec3 currentNormal = normals.at(std::stoi(vertexData.at(2)) - 1);
	
	uvsArray[vertexPointer * 2] = currentUV.x;
	uvsArray[vertexPointer * 2 + 1] = currentUV.y;

	normalsArray[vertexPointer * 2] = currentNormal.x;
	normalsArray[vertexPointer * 2 + 1] = currentNormal.y;
	normalsArray[vertexPointer * 2 + 2] = currentNormal.z;
}
