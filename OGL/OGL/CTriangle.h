#pragma once
#include "CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle(std::map<int,bool>& _keyMap);
    virtual ~CTriangle();
    void Start();
    void Input(GLFWwindow* window, int key, int scancode, int action, int mods);
    void Update(float _dt, CCamera& _camera);
    void Render();

	void SetAspectRatio(float _value)
	{
		aspectRatio = _value;
	}
protected:
	// Vertices coordinates
	GLfloat vertices[18] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	// Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		// Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	// Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	// Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	// Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f		// Inner down
	};

	// Indices for vertices order
	GLuint indices[9] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};



	std::map<int, bool>* keypresses = nullptr;

	float m_MovementSpeed = 1.f;

	float m_dt;

	float aspectRatio = 1.0f;

	GLfloat halfScreenWidth = 1920 / 2;
	GLfloat halfScreenHeight = 1080 / 2;

	GLfloat rotationX = 0.0f;
	GLfloat rotationY = 0.0f;
	const GLfloat rotationSpeed = 1;

	void Movement(float _dt)
	{
		if (UpdateVertexPositions(m_Velocity.x * _dt, m_Velocity.y * _dt, m_Velocity.z * _dt))
		{
			ShaderNonsense();
		}
	}

	void ShaderNonsense();
	bool UpdateVertexPositions(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);

};
