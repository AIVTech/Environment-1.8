#ifndef GAMEMATH_H
#define GAMEMATH_H

#include "Entity.h"
#include "FpsCamera.h"

class GameMath
{
public:

	static glm::mat4 createTransformationMatrix(Entity& entity)
	{
		glm::mat4 matrix = glm::mat4(1.0);
		matrix = glm::translate(matrix, entity.getPosition());
		matrix = glm::rotate(matrix, glm::radians(entity.getRotation().x), glm::vec3(1, 0, 0));
		matrix = glm::rotate(matrix, glm::radians(entity.getRotation().y), glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, glm::radians(entity.getRotation().z), glm::vec3(0, 0, 1));
		float scale = entity.getScale();
		matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
		return matrix;
	}


	static glm::mat4 createViewMatrix(FpsCamera& camera)
	{
		glm::mat4 matrix = glm::mat4(1.0);
		matrix = glm::rotate(matrix, glm::radians(camera.getPitch()), glm::vec3(1, 0, 0));	// Pitch
		matrix = glm::rotate(matrix, glm::radians(camera.getYaw()), glm::vec3(0, 1, 0));	// Yaw
		glm::vec3 cameraPos = camera.getPosition();
		glm::vec3 negativeCameraPos = glm::vec3(-cameraPos.x, -cameraPos.y, -cameraPos.z);
		matrix = glm::translate(matrix, negativeCameraPos);
		return matrix;
	}

};

#endif // !GAMEMATH_H