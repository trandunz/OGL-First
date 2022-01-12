#version 460 core

layout (location = 0) in vec3 l_position;
layout (location = 1) in vec3 l_normals;
layout (location = 2) in vec2 l_texCoords;

uniform mat4 u_MVP;

out vec3 o_position;
out vec3 o_normals;
out vec2 o_texCoords;

void main()
{
	o_texCoords = l_texCoords;
	o_position = l_position;
	gl_Position = u_MVP * vec4(o_position, 1.0);
}