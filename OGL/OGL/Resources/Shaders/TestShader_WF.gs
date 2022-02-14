#version 460 core

layout (triangles) in;
layout (line_strip, max_vertices=3) out;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec3 ViewPos;

in DATA
{
	vec3 Normal;
	vec2 TexCoords;
	mat4 ViewMat;
	mat4 ModelMat;
    vec3 ViewPos;

} data_in[];

void main()
{
	gl_Position = data_in[0].ViewMat * gl_in[0].gl_Position;
	Normal = data_in[0].Normal;
	TexCoords = data_in[0].TexCoords;
	FragPos = gl_in[0].gl_Position.xyz;
    ViewPos = data_in[0].ViewPos;
	EmitVertex();

	gl_Position = data_in[1].ViewMat * gl_in[1].gl_Position;
	Normal = data_in[1].Normal;
	TexCoords = data_in[1].TexCoords;
	FragPos = gl_in[1].gl_Position.xyz;
    ViewPos = data_in[1].ViewPos;
	EmitVertex();

	gl_Position = data_in[2].ViewMat * gl_in[2].gl_Position;
	Normal = data_in[2].Normal;
	TexCoords = data_in[2].TexCoords;
	FragPos = gl_in[2].gl_Position.xyz;
    ViewPos = data_in[2].ViewPos;
	EmitVertex();

	EndPrimitive();
}