#version 460 core

layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;

in vec3 i_normals; //Texcoords from Vertex Shader
in vec2 i_texCoords; //Normals from Vertex Shader

out vec3 o_normals; //Normals for Fragment Shader
out vec2 o_texCoords; //Texcoords for Fragment Shader

void main(void)
{
    o_normals = i_normals;
    o_texCoords = i_texCoords;
}