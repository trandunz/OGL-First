#version 460 core

layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

in DATA
{   
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    mat4 Projection;
} data_in[];

void main(void)
{
    gl_Position = data_in[0].Projection * gl_in[0].gl_Position;
    FragPos = data_in[0].FragPos;
    Normal = data_in[0].Normal;
    TexCoords = data_in[0].TexCoords;
    EmitVertex();

    gl_Position = data_in[1].Projection * gl_in[1].gl_Position;
    FragPos = data_in[1].FragPos;
    Normal = data_in[1].Normal;
    TexCoords = data_in[1].TexCoords;
    EmitVertex();

    gl_Position = data_in[2].Projection * gl_in[2].gl_Position;
    FragPos = data_in[2].FragPos;
    Normal = data_in[2].Normal;
    TexCoords = data_in[2].TexCoords;
    EmitVertex();

    EndPrimitive();
}