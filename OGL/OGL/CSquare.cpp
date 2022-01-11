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
	if (m_Texture)
		m_Texture->Delete();
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

	m_Copies[std::to_string(m_NumOfCopies)] = std::make_pair(m_RGBA_Copy, transform);
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
	for (auto& item : m_Copies)
	{
		m_LightingShader->Bind();
		// Shaded Box Color
		m_LightingShader->SetUniform3f("objectColor", 1.0f, 1.0f, 1.0f);
		// Light (Abstract)
		m_LightingShader->SetUniform3f("lightColor", item.second.first.x, item.second.first.y, item.second.first.z);
		m_LightingShader->SetUniformVec3f("lightPos", item.second.second.position);
		// View Position Of Shaded Box
		m_LightingShader->SetUniformVec3f("viewPos", m_Camera->Position);
		// Position Of Shaded Box
		SetMVPUniform(m_LightingShader, Transform{ glm::vec3(1,1,1), glm::vec3(0,0,0), glm::vec3(1,1,1) });
		// Draw Shaded Box
		m_Renderer.Draw(*m_LightCubeVAO, *m_IndexBuffer, *m_LightingShader);
		m_LightingShader->UnBind();

		// Light (Body)
		m_Shader->Bind();
		// Light Texture
		m_Texture->Bind();
		glActiveTexture(m_Texture->ID);
		m_Shader->SetUniform1i("LightTexture", m_Texture->ID);
		m_Shader->SetUniform4f("u_Color", item.second.first.x, item.second.first.y, item.second.first.z, item.second.first.w);
		SetMVPUniform();
		// Draw Light (No Shading)
		m_Renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
		m_Shader->UnBind();
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

	ProcessRotationSlider();

	ImGui::SliderFloat(": X Position", &transform.position.x, -100, 100);
	ImGui::SliderFloat(": Y Position", &transform.position.y, -100, 100);
	ImGui::SliderFloat(": Z Position", &transform.position.z, -100, 100);

	ImGui::SliderFloat(": X Scale", &transform.scale.x, -100, 100);
	ImGui::SliderFloat(": Y Scale", &transform.scale.y, -100, 100);
	ImGui::SliderFloat(": Z Scale", &transform.scale.z, -100, 100);

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
	
	m_Copies[std::to_string(m_NumOfCopies)] = std::make_pair(m_RGBA_Copy, Transform{ m_Camera->Position + glm::vec3(m_Camera->Front.x * 5, m_Camera->Front.y * 5, m_Camera->Front.z * 5), glm::vec3(0,0,0), glm::vec3(1,1,1) });
}

void Shape::CSquare::Movement(float _dt)
{
	UpdatePosition(m_InputVec.x * m_MovementSpeed * _dt, m_InputVec.y * m_MovementSpeed * _dt, m_InputVec.z * m_MovementSpeed * _dt);

	m_Copies["0"] = std::make_pair(glm::vec4({ m_Color[0], m_Color[1], m_Color[2], m_Color[3] }), transform);
}

void Shape::CSquare::ProcessRotationSlider()
{
	float rotX(glm::degrees(transform.rotation.x));
	float rotY(glm::degrees(transform.rotation.y));
	float rotZ(glm::degrees(transform.rotation.z));

	ImGui::SliderFloat(": X Rotation", &rotX, 0, 359);
	ImGui::SliderFloat(": Y Rotation", &rotY, 0, 359);
	ImGui::SliderFloat(": Z Rotation", &rotZ, 0, 359);

	transform.rotation.x = glm::radians(rotX);
	transform.rotation.y = glm::radians(rotY);
	transform.rotation.z = glm::radians(rotZ);
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
	{
		m_Shader = new Shader("Resources/Shaders/TestShader.vs", "", "Resources/Shaders/TestShader.fs");
		m_LightingShader = new Shader("Resources/Shaders/basic_lighting.vs", "", "Resources/Shaders/basic_lighting.fs");
	}

	CleanupPointer(m_Texture);
	if (m_Texture == nullptr)
	{
		m_Texture = new Texture("Resources/Textures/1.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	}

	m_LightingShader->Bind();
	CreateVBBasedOnType();

	CleanupPointer(m_LightCubeVAO);
	m_LightCubeVAO = new VertexArray();
	{
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_LightCubeVAO->AddBuffer(*m_VertBuffer, layout);
	}

	m_Shader->Bind();
	CleanupPointer(m_VertexArray);
	m_VertexArray = new VertexArray();
	{
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_VertexArray->AddBuffer(*m_VertBuffer, layout);
	}
	//CreateIBBasedOnType();
}

