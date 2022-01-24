#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <stb-master/stb_image.h>

#include "Shader.h"

class Texture
{
public:
	Texture(const char* image, const char* type,GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	~Texture();

	void texUnit(Shader& shader, const char* uniform, GLuint unit)
	{
		shader.Bind();
		shader.SetUniform1i(uniform, unit);
	}

	void Bind();
	void Unbind();
	void Delete();

	GLuint Unit;
	GLuint ID;
	GLenum Type;
	const char* type;
};
#endif