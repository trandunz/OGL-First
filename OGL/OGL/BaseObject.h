#pragma once
#include "NumptyBehavior.h"
#include "Shader.h"

class BaseObject : public NumptyBehavior
{
private:
	Shader* CustomShader;
	Shader* Defaultshader;
};

