#ifndef AABB_H
#define AABB_H

#include <glm\glm.hpp>

class AABB
{
public:
	float xMin;
	float xMax;

	float yMin;
	float yMax;

	float zMin;
	float zMax;

	void setWorldPosition(glm::vec3& worldPos)
	{
		
	}

private:
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	float scale = 1;
};

#endif