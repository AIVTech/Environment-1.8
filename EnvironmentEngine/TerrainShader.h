#pragma once

#include "ShaderBase.h"
#include "FpsCamera.h"
#include "GameMath.h"

class TerrainShader
{
public:
	TerrainShader();

	void start();
	void stop();
	void cleanUp();

	// loading uniforms
	void loadTransformationMatrix(glm::mat4 matrix)
	{
		ShaderBase::LoadMatrix4(transformationMatrixLocation, matrix);
	}

	void loadProjectionMatrix(glm::mat4 matrix)
	{
		ShaderBase::LoadMatrix4(projectionMatrixLocation, matrix);
	}

	void loadViewMatrix(FpsCamera camera)
	{
		glm::mat4 viewMatrix = GameMath::createViewMatrix(camera);
		ShaderBase::LoadMatrix4(viewMatrixLocation, viewMatrix);
	}

	~TerrainShader();

private:
	unsigned int programID;
	unsigned int vertexShaderID;
	unsigned int fragmentShaderID;

	const char* VERTEX_FILE = "terrainVertexShader.glsl";
	const char* FRAGMENT_FILE = "terrainFragmentShader.glsl";

	void getAllUniformLocations();
	void bindAttributes();

	// uniform variables locations
	unsigned int transformationMatrixLocation;
	unsigned int projectionMatrixLocation;
	unsigned int viewMatrixLocation;

};

