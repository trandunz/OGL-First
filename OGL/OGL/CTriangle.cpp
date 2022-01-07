#include "CTriangle.h"

CTriangle::CTriangle(std::map<int, bool>& _keyMap)
{
	keypresses = &_keyMap;

	CleanupPointer(m_Shader);
	m_Shader = new Shader("Resources/Shaders/TriangleShader.vs", "Resources/Shaders/TriangleShader.fs");
	m_Shader->Bind();

	//CleanupPointer(m_Texture);
	//m_Texture = new Texture("Resources/Textures/test.png");
	//m_Texture->Bind();
	//m_Shader->SetUniform1i("u_Texture", 0);
}

CTriangle::~CTriangle()
{
	CleanupPointer(m_VertBuffer);
	CleanupPointer(m_IndexBuffer);
	CleanupPointer(m_VertexArray);
	CleanupPointer(m_Texture);

	keypresses = nullptr;
}

void CTriangle::Start()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

void CTriangle::Update(float _dt)
{
	m_dt = _dt;
	Movement(m_dt);

	Render();
}

void CTriangle::Render()
{
	// Make Material For Other Uniforms
	m_Shader->Bind();
	m_Shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
	SetMVPUniform();

	// Draw
	m_Renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
}

void CTriangle::ShaderNonsense()
{
	CleanupPointer(m_VertBuffer);
	m_VertBuffer = new VertexBuffer(vertices, 4 * 4 * sizeof(float)); // 4 x 4 vertices

	CleanupPointer(m_VertexArray);
	m_VertexArray = new VertexArray();

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	m_VertexArray->AddBuffer(*m_VertBuffer, layout);

	CleanupPointer(m_IndexBuffer);
	m_IndexBuffer = new IndexBuffer(indices, 6);

	m_VertexArray->UnBind();
	m_VertBuffer->UnBind();
	m_IndexBuffer->UnBind();

	if (m_Shader)
		m_Shader->UnBind();
}

bool CTriangle::UpdateVertexPositions(float _x, float _y, float _z)
{
	bool moved = false;
	if (_x >= 0.000000001 || _x <= -0.000000001)
	{
		m_Position.x += _x;
		moved = true;
	}
	if (_y >= 0.000000001 || _y <= -0.000000001)
	{
		m_Position.y += _y;
		moved = true;
	}
	if (_z >= 0.000000001 || _z <= -0.000000001)
	{
		m_Position.z += _z;
		moved = true;
	}

	return moved;
}
