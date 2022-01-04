#pragma once
#include "CShape.h"

class CTriangle : public CShape
{
public:
    virtual ~CTriangle();
    void Start();
    void Input(GLFWwindow* window, int key, int scancode, int action, int mods);
    void Update(float _dt, GLFWwindow* _renderWindow);
    void Render();
private:
	// Vertices coordinates
	GLfloat vertices[24] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	// Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		// Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	// Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	// Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	// Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,		// Inner down
	};

	// Indices for vertices order
	GLuint indices[9] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};

	std::map<int, bool> keypresses;

	float m_MovementSpeed = 1.f;

	float m_dt;

	void Movement(float _dt)
	{
		if (UpdateVertexPositions(x * _dt, y * _dt, z * _dt))
		{
			ShaderNonsense();
		}
	}

	void ShaderNonsense();
	bool UpdateVertexPositions(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);
};
