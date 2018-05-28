#include "StaticEntityShader.h"

StaticEntityShader::StaticEntityShader()
{
	ShaderBase::SetupShader(programID, vertexShaderID, fragmentShaderID, VERTEX_FILE, FRAGMENT_FILE);
	bindAttributes();
	getAllUniformLocations();
}

StaticEntityShader::~StaticEntityShader()
{
}

void StaticEntityShader::bindAttributes()
{
	ShaderBase::BindAttribute(programID, 0, "vertexPosition");
	ShaderBase::BindAttribute(programID, 1, "textureCoordinate");
}

void StaticEntityShader::getAllUniformLocations()
{
	transformationMatrixLocation = ShaderBase::GetUniformLocation(programID, "transformationMatrix");
	projectionMatrixLocation = ShaderBase::GetUniformLocation(programID, "projectionMatrix");
	viewMatrixLocation = ShaderBase::GetUniformLocation(programID, "viewMatrix");
}

void StaticEntityShader::start()
{
	ShaderBase::StartProgram(programID);
}

void StaticEntityShader::stop()
{
	ShaderBase::StopProgram();
}

void StaticEntityShader::cleanUp()
{
	ShaderBase::CleanUp(programID, vertexShaderID, fragmentShaderID);
}
