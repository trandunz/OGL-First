#include "CTriangle.h"

CTriangle::CTriangle(std::map<int, bool>& _keyMap)
{
	keypresses = &_keyMap;
	CleanupPointer(m_Shader);
	m_Shader = new Shader("Resources/Shaders/TriangleShader.shader");
	m_Shader->Bind();
}

CTriangle::~CTriangle()
{
	CleanupPointer(m_VertBuffer);
	CleanupPointer(m_IndexBuffer);

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

void CTriangle::Update(float _dt, CCamera& _camera)
{
	m_dt = _dt;
	Movement(m_dt);

	Render();
}

void CTriangle::Render()
{
	m_Shader->Bind();
	m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

	m_VertexArray->Bind();
	m_IndexBuffer->Bind();

	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);
}

void CTriangle::ShaderNonsense()
{
	CleanupPointer(m_VertBuffer);
	m_VertBuffer = new VertexBuffer(vertices, sizeof(vertices));

	CleanupPointer(m_VertexArray);
	m_VertexArray = new VertexArray();

	CleanupPointer(m_IndexBuffer);
	m_IndexBuffer = new IndexBuffer(indices, 9);

	m_VertexArray->UnBind();

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	m_VertBuffer->UnBind();
	m_VertexArray->UnBind();

	// Bind the EBO to 0 so that we don't accidentally modify it
	// MAKE SURE TO UNBIND IT AFTER UNBINDING THE VAO, as the EBO is linked in the VAO
	// This does not apply to the VBO because the VBO is already linked to the VAO during glVertexAttribPointer
	m_IndexBuffer->UnBind();

	if (m_Shader)
		m_Shader->UnBind();

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
