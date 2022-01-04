#pragma once
#include "CShape.h"

class CCircle : public CShape
{
public:
    virtual ~CCircle();
    void Start();
    void Input(GLFWwindow* window, int key, int scancode, int action, int mods);
    void Update();
    void Render();

private:
	// Vertices coordinates
	Vector3 vertices[360]{};

	// Indices for vertices order
	GLuint indices[9] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};
};

