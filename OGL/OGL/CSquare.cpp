#include "CSquare.h"

CSquare::CSquare(std::map<int, bool>& _keyMap, Camera& _camera)
{
	m_KeyPresses = &_keyMap;
	m_Camera = &_camera;
}

CSquare::~CSquare()
{
	CleanupPointer(m_VertBuffer);
	CleanupPointer(m_IndexBuffer);
	CleanupPointer(m_VertexArray);
	CleanupPointer(m_Texture);
	CleanupPointer(m_Shader);
	m_Camera = nullptr;
	m_KeyPresses = nullptr;
}

void CSquare::Start()
{
	SetType(SHAPETYPE::CUBE);
	ShaderNonsense();

	m_Copies["Cube"] = std::make_pair(m_RGBA_Copy,m_Position);
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
			case GLFW_KEY_LEFT_SHIFT:
			{
				m_HoldingShift = true;
				break;
			}
			case GLFW_KEY_LEFT_CONTROL:
			{
				m_GrabCube = !m_GrabCube;

				(*m_KeyPresses)[item.first] = false;
				break;
			}
			case GLFW_KEY_UP:
			{
				if (m_HoldingShift)
				{
					m_Position.z -= 1.0f;
				}
				else
				{
					m_Position.y += 1.0f;
				}

				(*m_KeyPresses)[item.first] = false;
				break;
			}
			case GLFW_KEY_DOWN:
			{
				if (m_HoldingShift)
				{
					m_Position.z += 1.0f;
				}
				else
				{
					m_Position.y -= 1.0f;
				}

				(* m_KeyPresses)[item.first] = false;
				break;
			}
			case GLFW_KEY_RIGHT:
			{
				m_Position.x += 1.0f;

				(*m_KeyPresses)[item.first] = false;
				break;
			}
			case GLFW_KEY_LEFT:
			{
				m_Position.x -= 1.0f;

				(*m_KeyPresses)[item.first] = false;
				break;
			}

			default:
				break;
			}
		}
		else if (item.second == false)
		{
			switch (item.first)
			{
			case GLFW_KEY_LEFT_SHIFT:
			{
				m_HoldingShift = false;
				break;
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
	for (auto& item : m_Copies)
	{
		// Make Material For Other Uniforms
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", item.second.first.x, item.second.first.y, item.second.first.z, item.second.first.w);
		SetMVPUniform(item.second.second);

		// Draw
		m_Renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
	}

}

void CSquare::CreateCopy()
{
	m_NumOfCopies++;

	m_Copies[std::to_string(m_NumOfCopies)] = std::make_pair(m_RGBA_Copy, m_Camera->Position + glm::vec3(m_Camera->Front.x * 5, m_Camera->Front.y * 5, m_Camera->Front.z * 5));
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
	layout.Push<float>(3);
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
