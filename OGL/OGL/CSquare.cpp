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
	InitRender();

	m_Copies[std::to_string(m_NumOfCopies)] = std::make_pair(m_RGBA_Copy, Transform);
	CreateCopy();
	CreateCopy();
	CreateCopy();
}

void CSquare::CursorEnterCallback(GLFWwindow* _window, int _entered)
{
	if (_entered)
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

void CSquare::Input(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
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
					Transform.position.z -= 1.0f;
				}
				else
				{
					Transform.position.y += 1.0f;
				}

				(*m_KeyPresses)[item.first] = false;
				break;
			}
			case GLFW_KEY_DOWN:
			{
				if (m_HoldingShift)
				{
					Transform.position.z += 1.0f;
				}
				else
				{
					Transform.position.y -= 1.0f;
				}

				(* m_KeyPresses)[item.first] = false;
				break;
			}
			case GLFW_KEY_RIGHT:
			{
				Transform.position.x += 1.0f;

				(*m_KeyPresses)[item.first] = false;
				break;
			}
			case GLFW_KEY_LEFT:
			{
				Transform.position.x -= 1.0f;

				(*m_KeyPresses)[item.first] = false;
				break;
			}
			case GLFW_KEY_P:
			{
				Physics::TestCubeCollision(STransform{ glm::vec3(), glm::vec3(), glm::vec3(2.0f,2.0f,2.0f), 0.0f },
					glm::vec3(1,1,1));

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

		m_LightingShader->SetUniformVec3f("viewPos", m_Camera->Position);
		m_LightingShader->SetUniform1f("material.shininess", 32.0f);
		// directional light
		m_LightingShader->SetUniform3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
		m_LightingShader->SetUniform3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		m_LightingShader->SetUniform3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		m_LightingShader->SetUniform3f("dirLight.specular", 0.5f, 0.5f, 0.5f);
		// point lights
		m_LightingShader->SetUniformVec3f("pointLights[" + item.first + "].position", item.second.second.position);
		m_LightingShader->SetUniform3f("pointLights[" + item.first + "].ambient", 0.05f, 0.05f, 0.05f);
		m_LightingShader->SetUniform3f("pointLights[" + item.first + "].diffuse", abs(item.second.first.x - 0.2f), abs(item.second.first.y - 0.2f), abs(item.second.first.z - 0.2f));
		m_LightingShader->SetUniform3f("pointLights[" + item.first + "].specular", item.second.first.x, item.second.first.y, item.second.first.z);
		m_LightingShader->SetUniform1f("pointLights[" + item.first + "].constant", 1.0f);
		m_LightingShader->SetUniform1f("pointLights[" + item.first + "].linear", 0.09f);
		m_LightingShader->SetUniform1f("pointLights[" + item.first + "].quadratic", 0.032f);
		//
		// ....
	}

	// spotLights (just camera atm)
	m_LightingShader->SetUniformVec3f("spotLight.position", m_Camera->Position);
	m_LightingShader->SetUniformVec3f("spotLight.direction", m_Camera->Front);
	m_LightingShader->SetUniform3f("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	m_LightingShader->SetUniform3f("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	m_LightingShader->SetUniform3f("spotLight.specular", 1.0f, 1.0f, 1.0f);
	m_LightingShader->SetUniform1f("spotLight.constant", 1.0f);
	m_LightingShader->SetUniform1f("spotLight.linear", 0.09f);
	m_LightingShader->SetUniform1f("spotLight.quadratic", 0.032f);
	m_LightingShader->SetUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	m_LightingShader->SetUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

	for (auto& item : m_Copies)
	{
		// ....
		// 
		// Position Of Shaded Box
		SetMVPUniform(m_LightingShader, STransform{ glm::vec3(1,1,1), glm::vec3(0,0,0), glm::vec3(1,1,1) });
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
		SetMVPUniform(item.second.second);
		// Draw Light (No Shading)
		m_Renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
		m_Shader->UnBind();
	}
}

void CSquare::ImGuiHandler()
{
	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::Text("Rotation");
		{
			ProcessRotationSlider();
		}
		ImGui::Text("");
		ImGui::Text("Transform");
		{
			ImGui::SliderFloat(":X Transform", &Transform.position.x, -100, 100);
			ImGui::SliderFloat(":Y Transform", &Transform.position.y, -100, 100);
			ImGui::SliderFloat(":Z Transform", &Transform.position.z, -100, 100);
		}

		ImGui::Text("");
		ImGui::Text("Scale");
		{
			ImGui::SliderFloat(":X Scale", &Transform.scale.x, 0, 100);
			ImGui::SliderFloat(":Y Scale", &Transform.scale.y, 0, 100);
			ImGui::SliderFloat(":Z Scale", &Transform.scale.z, 0, 100);
		}
	}

	if (ImGui::CollapsingHeader("Renderer"))
	{
		ImGui::Text("Set Color Of 'cube'");
		ImGui::ColorEdit4("color", m_Color);
	}
}

void CSquare::SetCopyColour(float _r, float _g, float _b, float _a)
{
	m_RGBA_Copy.w = _a;
	m_RGBA_Copy.x = _r;  // R
	m_RGBA_Copy.y = _g;  // G
	m_RGBA_Copy.z = _b;  // B
}

void CSquare::CreateCopy()
{
	m_NumOfCopies++;
	
	m_Copies[std::to_string(m_NumOfCopies)] = std::make_pair(m_RGBA_Copy, STransform{ m_Camera->Position + glm::vec3(m_Camera->Front.x * 5, m_Camera->Front.y * 5, m_Camera->Front.z * 5), glm::vec3(0,0,0), glm::vec3(1,1,1) });
}

void Shape::CSquare::Movement(float _dt)
{
	UpdatePosition(m_InputVec.x * m_MovementSpeed * _dt, m_InputVec.y * m_MovementSpeed * _dt, m_InputVec.z * m_MovementSpeed * _dt);

	m_Copies["1"] = std::make_pair(glm::vec4({ m_Color[0], m_Color[1], m_Color[2], m_Color[3] }), Transform);
}

void Shape::CSquare::ProcessRotationSlider()
{
	float rotX(glm::degrees(Transform.rotation.x));
	float rotY(glm::degrees(Transform.rotation.y));
	float rotZ(glm::degrees(Transform.rotation.z));

	ImGui::SliderFloat(":X Rotation", &rotX, 0, 359);
	ImGui::SliderFloat(":Y Rotation", &rotY, 0, 359);
	ImGui::SliderFloat(":Z Rotation", &rotZ, 0, 359);

	Transform.rotation.x = glm::radians(rotX);
	Transform.rotation.y = glm::radians(rotY);
	Transform.rotation.z = glm::radians(rotZ);
}

void CSquare::InitRender(const char* _vsAddress, const char* _gsAddress, 
	const char* _fsAddress, const char* _texAddress, 
	VertexBufferLayout _vbLayouts)
{
	CleanupPointer(m_Shader);
	if (m_WireFrameMode)
	{
		m_Shader = new Shader("Resources/Shaders/TestShader.vs", "", "Resources/Shaders/TestShader.fs");
		m_LightingShader = new Shader(_vsAddress, _gsAddress, _fsAddress);
	}
	else
	{
		m_Shader = new Shader("Resources/Shaders/TestShader.vs", "", "Resources/Shaders/TestShader.fs");
		m_LightingShader = new Shader(_vsAddress, _gsAddress, _fsAddress);
	}

	CleanupPointer(m_Texture);
	if (m_Texture == nullptr)
	{
		m_Texture = new Texture(_texAddress, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	}

	m_LightingShader->Bind();
	CreateVBBasedOnType();

	CleanupPointer(m_LightCubeVAO);
	m_LightCubeVAO = new VertexArray();
	{
		_vbLayouts.Push<float>(3);
		_vbLayouts.Push<float>(3);
		_vbLayouts.Push<float>(2);
		m_LightCubeVAO->AddBuffer(*m_VertBuffer, _vbLayouts);
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

