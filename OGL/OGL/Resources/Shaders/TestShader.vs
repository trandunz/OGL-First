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

out DATA
{
	vec3 Normal;
	vec2 TexCoords;
	mat4 ViewMat;
	mat4 ModelMat;
	vec3 ViewPos;
} data_out;

uniform vec3 viewPos;

void main()
{
	
	gl_Position = instanceMatrix * vec4(l_position, 1.0);
	data_out.ViewMat = projection * view;
	data_out.TexCoords = l_texCoords;
	data_out.Normal = mat3(transpose(inverse(instanceMatrix))) * l_normals;  
	data_out.ModelMat = instanceMatrix;
	data_out.ViewPos = viewPos;
}