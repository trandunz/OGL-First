#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoord

out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0f);
	v_TexCoord = texCoord;
}