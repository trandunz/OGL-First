#define STB_IMAGE_IMPLEMENTATION

#include"Texture.h"

Texture::Texture(const char* _image, const char* _type,GLenum _texType, GLenum _slot, GLenum _format, GLenum _pixelType)
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
	// Assigns the texture to a Texture Unit
	glBindTexture(_texType, ID);

	// Assigns the image to the OpenGL Texture object
	GLint loadedComponents = (numColCh == 4) ? GL_RGBA : GL_RGB;
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
	// Assigns the texture to a Texture Unit
	glBindTexture(_texType, ID);

	// Assigns the image to the OpenGL Texture object
	GLint loadedComponents = (numColCh == 4) ? GL_RGBA : GL_RGB;
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

Texture::~Texture()
{
	Unbind();
	Delete();
}

void Texture::Bind()
{
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