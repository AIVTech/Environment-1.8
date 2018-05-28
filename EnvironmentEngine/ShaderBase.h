#pragma once

#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderBase
{
public:

	static void LoadFloat(unsigned int& location, float& value)
	{
		glUniform1f(location, value);
	}

	static void LoadInt(unsigned int& location, int& value)
	{
		glUniform1i(location, value);
	}

	static void LoadVector3(unsigned int& location, glm::vec3& vector)
	{
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	static void LoadBoolean(unsigned int& location, bool& state)
	{
		float value = 0;
		if (state)
		{
			value = 1;
		}
		glUniform1f(location, value);
	}

	static void LoadMatrix4(unsigned int& location, glm::mat4& matrix)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	}

	static void BindAttribute(unsigned int& programID, int attribute, const char* variable)
	{
		glBindAttribLocation(programID, attribute, variable);
	}

	static unsigned int GetUniformLocation(unsigned int& programID, const char* name)
	{
		return glGetUniformLocation(programID, name);
	}

	static void StartProgram(unsigned int& programID)
	{
		glUseProgram(programID);
	}

	static void StopProgram()
	{
		glUseProgram(0);
	}

	static void CleanUp(unsigned int& programID, unsigned int& vertexShaderID, unsigned int& fragmentShaderID)
	{
		StopProgram();
		glDetachShader(programID, vertexShaderID);
		glDetachShader(programID, fragmentShaderID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		glDeleteProgram(programID);
	}

	////////////////////////////////////////////////////////////////////////////////////////////

	static unsigned int CreateShader(const char* filepath, unsigned int type)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string shaderCode;
		std::ifstream shaderFile;
		// ensure ifstream objects can throw exceptions:
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			shaderFile.open(filepath);
			std::stringstream shaderStream;
			// read file's buffer contents into streams
			shaderStream << shaderFile.rdbuf();
			// close file handlers
			shaderFile.close();
			// convert stream into string
			shaderCode = shaderStream.str();
		}
		catch (std::ifstream::failure e)
		{ }
		const char* Code = shaderCode.c_str();
		unsigned int shaderID;
		shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &Code, NULL);
		glCompileShader(shaderID);
		CheckCompileErrors(shaderID, "Shader");

		return shaderID;
	}

	static unsigned int CreateProgram(unsigned int& vertexShaderID, unsigned int& fragmentShaderID)
	{
		unsigned int programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
		glLinkProgram(programID);
		glValidateProgram(programID);

		return programID;
	}

	static void SetupShader(unsigned int& programID, unsigned int& vertexShaderID, unsigned int& fragmentShaderID, const char* VERTEX_FILE, const char* FRAGMENT_FILE)
	{
		vertexShaderID = ShaderBase::CreateShader(VERTEX_FILE, GL_VERTEX_SHADER);
		fragmentShaderID = ShaderBase::CreateShader(FRAGMENT_FILE, GL_FRAGMENT_SHADER);
		programID = ShaderBase::CreateProgram(vertexShaderID, fragmentShaderID);
	}

private:
	static void CheckCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};

