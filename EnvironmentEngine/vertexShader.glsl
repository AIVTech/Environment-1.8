#version 400 core

in vec3 vertexPosition;
in vec2 textureCoordinate;

out vec2 pass_uvs;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main(void)
{
	vec4 worldPosition = transformationMatrix * vec4(vertexPosition, 1.0);
	gl_Position = projectionMatrix * viewMatrix * worldPosition;
	pass_uvs = textureCoordinate;
}