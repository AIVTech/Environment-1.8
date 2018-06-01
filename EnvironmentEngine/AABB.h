#ifndef AABB_H
#define AABB_H

#include <glm\glm.hpp>
#include <iostream>

class AABB
{
public:
	float xMin;
	float xMax;

	float yMin;
	float yMax;

	float zMin;
	float zMax;

	static void setWorldPosition(AABB* box, glm::vec3& newPos)
	{
		float boxCenterX = (box->xMax + box->xMin) / 2;
		float boxCenterY = (box->yMax + box->yMin) / 2;
		float boxCenterZ = (box->zMax + box->zMin) / 2;

		float translationX = newPos.x - boxCenterX;
		float translationY = newPos.y - boxCenterY;
		float translationZ = newPos.z - boxCenterZ;
		
		box->xMax += translationX;
		box->xMin += translationX;

		box->yMax += translationY;
		box->yMin += translationY;

		box->zMax += translationZ;
		box->zMin += translationZ;
	}

	glm::vec3 getCenterPosition()
	{
		float boxCenterX = (this->xMax + this->xMin) / 2;
		float boxCenterY = (this->yMax + this->yMin) / 2;
		float boxCenterZ = (this->zMax + this->zMin) / 2;

		return glm::vec3(boxCenterX, boxCenterY, boxCenterZ);
	}

private:
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	float scale = 1;
};

#endif