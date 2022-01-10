#include "CSquare.h"
using namespace Shape;

CSquare::CSquare(std::map<int, bool>& _keyMap, Camera& _camera)
{
	m_KeyPresses = &_keyMap;
	m_Camera = &_camera;

	Start();
}

CSquare::~CSquare()
{
	CleanupPointer(m_VertBuffer);
	CleanupPointer(m_IndexBuffer);
	CleanupPointer(m_VertexArray);
	CleanupPointer(m_Texture);
	CleanupPointer(m_LightingShader);
	CleanupPointer(m_Shader);
	CleanupPointer(m_LightCubeVAO);
	m_Camera = nullptr;
	m_KeyPresses = nullptr;
}

void CSquare::Start()
{
	SetType(TYPE::CUBE);
	ShaderNonsense();

	m_Copies[std::to_string(m_NumOfCopies)] = std::make_pair(m_RGBA_Copy, transform.position);
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
					transform.position.z -= 1.0f;
				}
				else
				{
					transform.position.y += 1.0f;
				}

				(*m_KeyPresses)[item.first] = false;
				break;
			}
			case GLFW_KEY_DOWN:
			{
				if (m_HoldingShift)
				{
					transform.position.z += 1.0f;
				}
				else
				{
					transform.position.y -= 1.0f;
				}

				(* m_KeyPresses)[item.first] = false;
				break;
			}
			case GLFW_KEY_RIGHT:
			{
				transform.position.x += 1.0f;

				(*m_KeyPresses)[item.first] = false;
				break;
			}
			case GLFW_KEY_LEFT:
			{
				transform.position.x -= 1.0f;

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

	ImGuiHandler();
}

void CSquare::Render()
{
	int i = 0;
	for (auto& item : m_Copies)
	{
		m_LightingShader->Bind();
		m_LightingShader->SetUniform3f("objectColor", 1.0f, 1.0f, 1.0f);
		m_LightingShader->SetUniform3f("lightColor", item.second.first.x, item.second.first.y, item.second.first.z);
		m_LightingShader->SetUniformVec3f("lightPos", item.second.second);
		m_LightingShader->SetUniformVec3f("viewPos", m_Camera->Position);
		std::string Uniform_pos = "m_PointLights[" + std::to_string(i) + "].position";
		m_LightingShader->SetUniformVec3f(Uniform_pos, item.second.second);
		std::string Uniform_const = "m_PointLights[" + std::to_string(i) + "].constant";
		m_LightingShader->SetUniform1f(Uniform_const, 1.0f);
		SetMVPUniform(m_LightingShader);
		m_Renderer.Draw(*m_LightCubeVAO, *m_IndexBuffer, *m_LightingShader);

		// Make Material For Other Uniforms
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", item.second.first.x, item.second.first.y, item.second.first.z, item.second.first.w);
		SetMVPUniform(item.second.second);
		m_Renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);

	}
}

void Shape::CSquare::ImGuiHandler()
{
	ImGui::BeginMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Close", "Ctrl+W")) { m_ToolActive = false; }
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Tools"))
	{
		if (ImGui::MenuItem("WireFrame Mode"))
		{
			m_WireFrameMode = !m_WireFrameMode;
			ShaderNonsense();
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Copy"))
	{
		if (ImGui::MenuItem("Red", " : Create Copy Of Color"))
		{
			SetCopyColour(1, 0, 0, 1);
			CreateCopy();
		}
		if (ImGui::MenuItem("Blue", " : Create Copy Of Color"))
		{
			SetCopyColour(0, 0, 1, 1);
			CreateCopy();
		}
		if (ImGui::MenuItem("Green", " : Create Copy Of Color"))
		{
			SetCopyColour(0, 1, 0, 1);
			CreateCopy();
		}
		if (ImGui::MenuItem("Current", " : Create Copy Of Color"))
		{
			SetCopyColour(m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
			CreateCopy();
		}
		ImGui::EndMenu();
	}
	ImGui::EndMenuBar();

	ImGui::Text("Set Shape (Broken)");
	if (ImGui::Button("Square"))
	{
		SetType(TYPE::SQUARE);
		ShaderNonsense();
	}
	if (ImGui::Button("Cube"))
	{
		SetType(TYPE::CUBE);
		ShaderNonsense();
	}
	if (ImGui::Button("Triangle"))
	{
		SetType(TYPE::TRIANGLE);
		ShaderNonsense();
	}
	ImGui::Text("Set Color Of 'cube'");
	ImGui::ColorEdit4("color", m_Color);

	// Display contents in a scrolling region
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Console Output");
	ImGui::BeginChild("Scrolling");
	for (int n = 0; n < 50; n++)
		ImGui::Text("%04d: Niggers", n);
	ImGui::EndChild();
}

inline void Shape::CSquare::SetCopyColour(float _r, float _g, float _b, float _a)
{
	m_RGBA_Copy.w = _a;
	m_RGBA_Copy.x = _r;  // R
	m_RGBA_Copy.y = _g;  // G
	m_RGBA_Copy.z = _b;  // B
}

void CSquare::CreateCopy()
{
	m_NumOfCopies++;

	m_Copies[std::to_string(m_NumOfCopies)] = std::make_pair(m_RGBA_Copy, m_Camera->Position + glm::vec3(m_Camera->Front.x * 5, m_Camera->Front.y * 5, m_Camera->Front.z * 5));
}

void Shape::CSquare::Movement(float _dt)
{
	UpdatePosition(m_InputVec.x * m_MovementSpeed * _dt, m_InputVec.y * m_MovementSpeed * _dt, m_InputVec.z * m_MovementSpeed * _dt);

	m_Copies["0"] = std::make_pair(glm::vec4({ m_Color[0], m_Color[1], m_Color[2], m_Color[3] }), transform.position);
}

void CSquare::ShaderNonsense()
{
	CleanupPointer(m_Shader);
	if (m_WireFrameMode)
	{
		m_Shader = new Shader("Resources/Shaders/TestShader.vs", "", "Resources/Shaders/TestShader.fs");
		m_LightingShader = new Shader("Resources/Shaders/basic_lighting.vs", "", "Resources/Shaders/basic_lighting.fs");
	}
	else
		m_Shader = new Shader("Resources/Shaders/TestShader.vs", "", "Resources/Shaders/TestShader.fs");
		m_LightingShader = new Shader("Resources/Shaders/basic_lighting.vs", "", "Resources/Shaders/basic_lighting.fs");

	m_LightingShader->Bind();
	CreateVBBasedOnType();

	CleanupPointer(m_LightCubeVAO);
	m_LightCubeVAO = new VertexArray();
	{
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		m_LightCubeVAO->AddBuffer(*m_VertBuffer, layout);
	}

	m_Shader->Bind();
	
	CleanupPointer(m_VertexArray);
	m_VertexArray = new VertexArray();
	{
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		m_VertexArray->AddBuffer(*m_VertBuffer, layout);
	}
	//CreateIBBasedOnType();
}

