#pragma once
#include "NumptyBehavior.h"
class Cubemap :
    public NumptyBehavior
{
public:
	Cubemap(std::vector<std::string> faces);

	void Bind();
	void Unbind();
	void Delete();

	GLuint ID;
	GLenum type;
};

