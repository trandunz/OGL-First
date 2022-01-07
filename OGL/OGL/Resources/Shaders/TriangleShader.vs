#version 460 core

layout (location = 0) in vec4 position;

out vec4 vertexColor;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	vertexColor = vec4(0.5f, 0.0f,0.0f,1.0f);
}