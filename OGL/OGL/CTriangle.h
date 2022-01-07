#pragma once
#include "CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle(std::map<int,bool>& _keyMap);
    virtual ~CTriangle();
    void Start();
    void Input(GLFWwindow* window, int key, int scancode, int action, int mods);
    void Update(float _dt);
    void Render();

	inline void SetMVPUniform()
	{
		model = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
	}
protected:
	// Vertices coordinates
	GLfloat vertices[16] =
	{
		//-0.5f, -0.5f/* * float(sqrt(3)) / 3*/, 0.0f,	
		//0.5f, -0.5f/* * float(sqrt(3)) / 3*/, 0.0f,		
		//0.0f, 0.5f/* * float(sqrt(3)) * 2 / 3*/, 0.0f,	
		//-0.5f/* / 2*/, 0.5f/* * float(sqrt(3)) / 6*/, 0.0f,
		////0.5f/* / 2*/, 0.5f/* * float(sqrt(3)) / 6*/, 0.0f,
		////0.0f, -0.5f/* * float(sqrt(3)) / 3*/, 0.0f,		
		-0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		-0.5, 0.5f, 0.0f, 1.0f
	};

	// Indices for vertices order
	GLuint indices[6] =
	{
		0, 1, 2, // Lower left triangle
		2, 3, 0, // Lower right triangle
	};

	VertexBuffer* m_VertBuffer = nullptr;
	IndexBuffer* m_IndexBuffer = nullptr;
	VertexArray* m_VertexArray = nullptr;
	Texture* m_Texture = nullptr;

	glm::mat4 proj = glm::ortho(-16.0f / m_Scale, 16.0f / m_Scale, -9.0f / m_Scale, 9.0f / m_Scale, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-1, 0, 0));
	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position);

	std::map<int, bool>* keypresses = nullptr;

	float m_dt;

	glm::vec3 m_Position = { 0, 0, 0 };
	float m_MovementSpeed = 1.0f;

	void Movement(float _dt)
	{
		if (UpdateVertexPositions(m_Velocity.x * _dt, m_Velocity.y * _dt, m_Velocity.z * _dt))
		{
			//ShaderNonsense();
		}
	}

	void ShaderNonsense();
	bool UpdateVertexPositions(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);

};
