#include "CTriangle.h"

CTriangle::CTriangle(std::map<int, bool>& _keyMap)
{
	keypresses = &_keyMap;
}

CTriangle::~CTriangle()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(m_ShaderProgram);

	keypresses = nullptr;
}

void CTriangle::Start()
{
	ShaderNonsense();
}

void CTriangle::Input(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	m_Velocity.x = 0.0f;
	m_Velocity.y = 0.0f;
	m_Velocity.z = 0.0f;

	for (auto& item : (*keypresses))
	{
		if (item.second == true)
		{
			switch (item.first)
			{
			case GLFW_KEY_D:
			{
				m_Velocity.x += m_MovementSpeed;
				break;
			}
			case GLFW_KEY_A:
			{
				m_Velocity.x -= m_MovementSpeed;
				break;
			}
			case GLFW_KEY_W:
			{
				m_Velocity.y += m_MovementSpeed;
				break;
			}
			case GLFW_KEY_S:
			{
				m_Velocity.y -= m_MovementSpeed;
			}
			
			case GLFW_KEY_LEFT_SHIFT:
			{
				m_Velocity.z += m_MovementSpeed;
			}
			case GLFW_KEY_LEFT_CONTROL:
			{
				m_Velocity.z -= m_MovementSpeed;
				break;
			}
			default:
				break;
			}
		}
	}
	
	if (m_Velocity.y > m_MovementSpeed)
	{
		m_Velocity.y = m_MovementSpeed;
	}
	else if (m_Velocity.y < -m_MovementSpeed)
	{
		m_Velocity.y = -m_MovementSpeed;
	}

	if (m_Velocity.x > m_MovementSpeed)
	{
		m_Velocity.x = m_MovementSpeed;
	}
	else if (m_Velocity.x < -m_MovementSpeed)
	{
		m_Velocity.x = -m_MovementSpeed;
	}

	if (m_Velocity.z > m_MovementSpeed)
	{
		m_Velocity.z = m_MovementSpeed;
	}
	else if (m_Velocity.z < -m_MovementSpeed)
	{
		m_Velocity.z = -m_MovementSpeed;
	}
}

void CTriangle::Update(float _dt, GLFWwindow* _renderWindow)
{
	m_dt = _dt;
	Movement(m_dt);
	
	Render();
}

void CTriangle::Render()
{
	glUseProgram(m_ShaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}

void CTriangle::ShaderNonsense()
{
	if (m_ShaderProgram)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);

		glDeleteVertexArrays(0, &VAO);
		glDeleteBuffers(0, &VBO);
		glDeleteBuffers(0, &EBO);

		glDeleteProgram(m_ShaderProgram);
	}

	m_ShaderProgram = CShaderLoader::CreateShaderProgram("Resources/Shaders/TriangleShader.vs", "Resources/Shaders/TriangleShader.fs");
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// Introduce the indices into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Bind the EBO to 0 so that we don't accidentally modify it
	// MAKE SURE TO UNBIND IT AFTER UNBINDING THE VAO, as the EBO is linked in the VAO
	// This does not apply to the VBO because the VBO is already linked to the VAO during glVertexAttribPointer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool CTriangle::UpdateVertexPositions(float _x, float _y, float _z)
{
	bool moved = false;
	if (_x >= 0.000000001 || _x <= -0.000000001)
	{
		vertices[0] += _x;
		vertices[3] += _x;
		vertices[6] += _x;
		vertices[9] += _x;
		vertices[12] += _x;
		vertices[15] += _x;
		moved = true;
	}
	if (_y >= 0.000000001 || _y <= -0.000000001)
	{
		vertices[1] += _y;
		vertices[4] += _y;
		vertices[7] += _y;
		vertices[10] += _y;
		vertices[13] += _y;
		vertices[16] += _y;
		moved = true;
	}
	if (_z >= 0.000000001 || _z <= -0.000000001)
	{
		vertices[2] += _z;
		vertices[5] += _z;
		vertices[8] += _z;
		vertices[11] += _z;
		vertices[14] += _z;
		vertices[17] += _z;
		moved = true;
	}

	return moved;
}
