#version 460 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 ViewPos;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

out vec4 FragColor;

void main()
{
    FragColor = texture(u_Texture, TexCoords) * u_Color;
} 