#include "CSquare.h"

CSquare::CSquare(std::map<int, bool>& _keyMap)
{
	m_KeyPresses = &_keyMap;
}

CSquare::~CSquare()
{
	CleanupPointer(m_VertBuffer);
	CleanupPointer(m_IndexBuffer);
	CleanupPointer(m_VertexArray);
	CleanupPointer(m_Texture);
	CleanupPointer(m_Shader);

	m_KeyPresses = nullptr;
}

void CSquare::Start()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SetType(SHAPETYPE::SQUARE);
	ShaderNonsense();
}

void CSquare::CursorEnterCallback(GLFWwindow* window, int entered)
{
	if (entered)
	{
		m_InputVec.x = 0;
		m_InputVec.y = 0;
		m_InputVec.z = 0;
	}
	else
	{
		m_InputVec.x = 0;
		m_InputVec.y = 0;
		m_InputVec.z = 0;
	}
}

void CSquare::Input(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	m_InputVec.x = 0.0f;
	m_InputVec.y = 0.0f;
	m_InputVec.z = 0.0f;

	for (auto& item : (*m_KeyPresses))
	{
		if (item.second == true)
		{
			switch (item.first)
			{
			case GLFW_KEY_D:
			{
				m_InputVec.x = 1;
				break;
			}
			case GLFW_KEY_A:
			{
				m_InputVec.x = -1;
				break;
			}
			case GLFW_KEY_W:
			{
				m_InputVec.y = 1;
				break;
			}
			case GLFW_KEY_S:
			{
				m_InputVec.y = -1;
			}
			default:
				break;
			}
		}
	}

	glm::normalize(m_InputVec);
}

void CSquare::Update(long double& _dt)
{
	m_dt = _dt;
	Movement(m_dt);

	Render();
}

void CSquare::Render()
{
	// Make Material For Other Uniforms
	m_Shader->Bind();
	m_Shader->SetUniform4f("u_Color", m_RGBA.x, m_RGBA.y, m_RGBA.z, m_RGBA.w);
	SetMVPUniform();

	// Draw
	m_Renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
}

void CSquare::ShaderNonsense()
{
	CleanupPointer(m_Shader);
	if (m_WireFrameMode)
		m_Shader = new Shader("Resources/Shaders/TestShader.vs", "Resources/Shaders/TestShader_WF.gs", "Resources/Shaders/TestShader.fs");
	else
		m_Shader = new Shader("Resources/Shaders/TestShader.vs", "Resources/Shaders/TestShader_FILL.gs", "Resources/Shaders/TestShader.fs");
	
	m_Shader->Bind();

	CreateVBBasedOnType();

	CleanupPointer(m_VertexArray);
	m_VertexArray = new VertexArray();

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	m_VertexArray->AddBuffer(*m_VertBuffer, layout);

	CreateIBBasedOnType();
}

bool CSquare::UpdatePosition(float _x, float _y, float _z)
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
