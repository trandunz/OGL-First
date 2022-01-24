#version 460 core

layout (location = 0) in vec3 l_position;
layout (location = 1) in vec3 l_normals;
layout (location = 2) in vec2 l_texCoords;
layout (location = 3) in mat4 instanceMatrix;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};


out vec3 o_normals;
out vec2 o_texCoords;

void main()
{
	o_texCoords = l_texCoords;
	gl_Position = projection * view * instanceMatrix * vec4(l_position, 1.0);
}