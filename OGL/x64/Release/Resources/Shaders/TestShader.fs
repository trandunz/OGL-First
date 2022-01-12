#version 460 core

in vec3 o_position;
in vec3 o_normals;
in vec2 o_texCoords;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

out vec4 FragColor;

void main()
{
    FragColor = texture(u_Texture, o_texCoords) * u_Color;
} 