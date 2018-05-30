#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "GameMath.h"

using namespace glm;

class AABB
{
public:
	AABB() {}
	AABB(
		vec3 center,

		vec3 topRightFar,
		vec3 topRightNear,
		vec3 topLeftFar,
		vec3 topLeftNear,

		vec3 bottomRightFar,
		vec3 bottomRightNear,
		vec3 bottomLeftFar,
		vec3 bottompLeftNear
	)
	{
		this->topRightFar = topRightFar;
		this->topRightNear = topRightNear;
		this->topLeftFar = topLeftFar;
		this->topLeftNear = topLeftNear;

		this->bottomRightFar = bottomRightFar;
		this->bottomRightNear = bottomRightNear;
		this->bottomLeftFar = bottomLeftFar;
		this->bottompLeftNear = bottompLeftNear;
		
		this->position = position;
	}

	void setPosition(glm::vec3& pos) { updateBoxVertices(); position = pos; }
	void setRotation(glm::vec3& rot) { rotation = rot; }
	void setScale(float& value) { scale = value; }

	glm::vec3& getPosition() { return position; }
	glm::vec3& getRotation() { return rotation; }
	float& getScale() { return scale; }

	vec3 topRightFar;
	vec3 topRightNear;
	vec3 topLeftFar;
	vec3 topLeftNear;

	vec3 bottomRightFar;
	vec3 bottomRightNear;
	vec3 bottomLeftFar;
	vec3 bottompLeftNear;

	static AABB* constructAABB(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
	{
		vec3 topRightFar;
		vec3 topRightNear;
		vec3 topLeftFar;
		vec3 topLeftNear;

		vec3 bottomRightFar;
		vec3 bottomRightNear;
		vec3 bottomLeftFar;
		vec3 bottompLeftNear;

		topRightFar = vec3(xMax, yMax, zMax);
		topRightNear = vec3(xMax, yMax, zMin);
		topLeftFar = vec3(xMin, yMax, zMax);
		topLeftNear = vec3(xMin, yMax, zMin);

		bottomRightFar = vec3(xMax, yMin, zMax);
		bottomRightNear = vec3(xMax, yMin, zMin);
		bottomLeftFar = vec3(xMin, yMin, zMax);
		bottompLeftNear = vec3(xMin, yMin, zMin);

		float xAvg = (xMax + xMin) / 2;
		float yAvg = (yMax + yMin) / 2;
		float zAvg = (zMax + zMin) / 2;

		vec3 center = vec3(xAvg, yAvg, zAvg);

		return new AABB(
			center,
			topRightFar,
			topRightNear,
			topLeftFar,
			topLeftNear,
			bottomRightFar,
			bottomRightNear,
			bottomLeftFar,
			bottompLeftNear
		);
	}

	~AABB() {}

private:
	vec3 position;
	vec3 rotation;
	float scale;

	void updateBoxVertices()
	{
		//mat4 transformation = GameMath::createTransformationMatrix(position, rotation, scale);
		// top vertices
		//vec4 topRightFarNew = vec4(topRightFar.x, topRightFar.y, topRightFar.z, 1) * transformation;
		//topRightFar = vec3(topRightFarNew.x, topRightFarNew.y, topRightFarNew.z);
		//topRightFar = vec3(vec4());
		//vec3 r = vec3(vec4(1.0));
	}
};
