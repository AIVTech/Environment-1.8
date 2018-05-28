#ifndef OBJFILELOADER_H
#define OBJFILELOADER_H

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Model.h"
#include "StaticLoader.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <iterator>

class OBJFileLoader
{
public:
	OBJFileLoader();

	static Model loadObjModel(const char* modelPath, const char* texturePath, StaticLoader loader);

	~OBJFileLoader();

private:
	static void processVertex(std::vector<std::string>& vertexData, std::vector<int>& out_indices, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals,
		float* uvsArray, float* normalsArray);

	static std::vector<std::string> lineSplit(std::string str, std::string token) {
		std::vector<std::string>result;
		while (str.size()) {
			int index = str.find(token);
			if (index != std::string::npos) {
				result.push_back(str.substr(0, index));
				str = str.substr(index + token.size());
				if (str.size() == 0)result.push_back(str);
			}
			else {
				result.push_back(str);
				str = "";
			}
		}
		return result;
	}
};

#endif // !OBJFILELOADER_H