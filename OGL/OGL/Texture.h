#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <stb-master/stb_image.h>

#include "Shader.h"

class Texture
{
public:
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	void Bind();
	void Unbind();
	void Delete();

	GLuint ID;
	GLenum Type;
};
#endif