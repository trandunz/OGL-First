#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H
#include "Includes.h"
#include <stb-master/stb_image.h>

namespace Harmony
{
	class Texture
	{
	public:
		Texture() = default;
		Texture(const char* image, const char* type, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
		Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
		Texture(const char* image, GLenum slot, GLenum format);

		~Texture();

		void Bind();
		void Unbind();
		void Delete();

		GLuint Unit;
		GLuint ID;
		GLenum Type;
		std::string type;
	};
}

#endif