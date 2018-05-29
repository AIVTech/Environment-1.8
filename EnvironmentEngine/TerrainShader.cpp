#include "TerrainShader.h"

TerrainShader::TerrainShader()
{
	ShaderBase::SetupShader(programID, vertexShaderID, fragmentShaderID, VERTEX_FILE, FRAGMENT_FILE);
	bindAttributes();
	getAllUniformLocations();
}

TerrainShader::~TerrainShader()
{
}

void TerrainShader::bindAttributes()
{
	ShaderBase::BindAttribute(programID, 0, "vertexPosition");
	ShaderBase::BindAttribute(programID, 1, "textureCoordinate");
}

void TerrainShader::getAllUniformLocations()
{
	transformationMatrixLocation = ShaderBase::GetUniformLocation(programID, "transformationMatrix");
	projectionMatrixLocation = ShaderBase::GetUniformLocation(programID, "projectionMatrix");
	viewMatrixLocation = ShaderBase::GetUniformLocation(programID, "viewMatrix");
}

void TerrainShader::start()
{
	ShaderBase::StartProgram(programID);
}

void TerrainShader::stop()
{
	ShaderBase::StopProgram();
}

void TerrainShader::cleanUp()
{
	ShaderBase::CleanUp(programID, vertexShaderID, fragmentShaderID);
}
