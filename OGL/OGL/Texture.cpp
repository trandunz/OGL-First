#define STB_IMAGE_IMPLEMENTATION

#include"Texture.h"

namespace Harmony
{
	Texture::Texture(const char* _image, const char* _type, GLenum _texType, GLenum _slot, GLenum _format, GLenum _pixelType)
	{
		// Assigns the type of the texture ot the texture object
		type = _type;
		Type = _texType;

		// Stores the width, height, and the number of color channels of the image
		int widthImg, heightImg, numColCh;
		// Flips the image so it appears right side up
		stbi_set_flip_vertically_on_load(true);
		// Reads the image from a file and stores it in bytes
		unsigned char* bytes = stbi_load(_image, &widthImg, &heightImg, &numColCh, 0);


		// Generates an OpenGL texture object
		glGenTextures(1, &ID);
		glActiveTexture(GL_TEXTURE0 + _slot);
		Unit = _slot;
		// Assigns the texture to a Texture Unit
		glBindTexture(_texType, ID);

		// Assigns the image to the OpenGL Texture object
		GLint loadedComponents = 0;
		if (numColCh == 4)
		{
			loadedComponents = GL_SRGB_ALPHA;
		}
		else if (numColCh == 3)
		{
			loadedComponents = GL_SRGB;
		}
		else if (numColCh == 1)
		{
			loadedComponents = GL_SRGB;
		}
		else
		{
			loadedComponents = GL_RGB;
		}
		glTexImage2D(_texType, 0, loadedComponents, widthImg, heightImg, 0, _format, _pixelType, bytes);

		// Generates MipMaps
		glGenerateMipmap(_texType);

		// Deletes the image data as it is already in the OpenGL Texture object
		stbi_image_free(bytes);

		//// Configures the type of algorithm that is used to make the image smaller or bigger
		glTexParameteri(_texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(_texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Configures the way the texture repeats (if it does at all)
		glTexParameteri(_texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(_texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		// Unbinds the OpenGL Texture object so that it can't accidentally be modified
		glBindTexture(_texType, 0);
	}

	Texture::Texture(const char* _image, GLenum _texType, GLenum _slot, GLenum _format, GLenum _pixelType)
	{
		Type = _texType;

		// Stores the width, height, and the number of color channels of the image
		int widthImg, heightImg, numColCh;
		// Flips the image so it appears right side up
		stbi_set_flip_vertically_on_load(true);
		// Reads the image from a file and stores it in bytes
		unsigned char* bytes = stbi_load(_image, &widthImg, &heightImg, &numColCh, 0);


		// Generates an OpenGL texture object
		glGenTextures(1, &ID);
		glActiveTexture(GL_TEXTURE0 + _slot);
		Unit = _slot;
		// Assigns the texture to a Texture Unit
		glBindTexture(_texType, ID);

		// Assigns the image to the OpenGL Texture object
		GLint loadedComponents = 0;
		if (numColCh == 4)
		{
			loadedComponents = GL_SRGB_ALPHA;
		}
		else if (numColCh == 3)
		{
			loadedComponents = GL_SRGB;
		}
		else if (numColCh == 1)
		{
			loadedComponents = GL_SRGB;
		}
		else
		{
			loadedComponents = GL_RGB;
		}

		glTexImage2D(_texType, 0, loadedComponents, widthImg, heightImg, 0, _format, _pixelType, bytes);

		// Generates MipMaps
		glGenerateMipmap(_texType);

		// Deletes the image data as it is already in the OpenGL Texture object
		stbi_image_free(bytes);

		//// Configures the type of algorithm that is used to make the image smaller or bigger
		glTexParameteri(_texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(_texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Configures the way the texture repeats (if it does at all)
		glTexParameteri(_texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(_texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		// Unbinds the OpenGL Texture object so that it can't accidentally be modified
		glBindTexture(_texType, 0);
	}

	Texture::Texture(const char* _image, GLenum _slot, GLenum _format)
	{
		Type = GL_TEXTURE_2D;
		// Stores the width, height, and the number of color channels of the image
		int widthImg, heightImg, channels;
		// Flips the image so it appears right side up
		stbi_set_flip_vertically_on_load(true);
		// Reads the image from a file and stores it in bytes
		unsigned char* bytes = stbi_load(_image, &widthImg, &heightImg, &channels, 0);


		// Generates an OpenGL texture object
		glGenTextures(1, &ID);
		glActiveTexture(GL_TEXTURE0 + _slot);
		Unit = _slot;
		// Assigns the texture to a Texture Unit
		glBindTexture(GL_TEXTURE_2D, ID);
		GLenum format;
		switch (channels)
		{
		case 1:
			format = GL_RED;
			break;
		case 2:
			format = GL_RG;
			break;
		case 3:
			format = GL_SRGB;
			break;
		case 4:
			format = GL_SRGB_ALPHA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, widthImg, heightImg, 0, _format, GL_UNSIGNED_BYTE, bytes);

		// Generates MipMaps
		glGenerateMipmap(GL_TEXTURE_2D);

		// Deletes the image data as it is already in the OpenGL Texture object
		stbi_image_free(bytes);

		//// Configures the type of algorithm that is used to make the image smaller or bigger
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Configures the way the texture repeats (if it does at all)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		// Unbinds the OpenGL Texture object so that it can't accidentally be modified
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		Unbind();
		Delete();
	}

	void Texture::Bind()
	{
		glActiveTexture(GL_TEXTURE0 + Unit);
		glBindTexture(Type, ID);
	}

	void Texture::Unbind()
	{
		glBindTexture(Type, 0);
	}

	void Texture::Delete()
	{
		glDeleteTextures(1, &ID);
	}
}
