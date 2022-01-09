#pragma once
#include "CShape.h"
#include "GUI.h"

class CSquare : public CShape
{
public:
	CSquare(std::map<int,bool>& _keyMap, Camera& _camera);
    virtual ~CSquare();
    void Start();
	void CursorEnterCallback(GLFWwindow* window, int entered);
    void Input(GLFWwindow* window, int key, int scancode, int action, int mods);
	void Update(long double& _dt);
    void Render();
	void ImGuiHandler()
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
			SetType(SHAPETYPE::SQUARE);
			ShaderNonsense();
		}
		if (ImGui::Button("Cube"))
		{
			SetType(SHAPETYPE::CUBE);
			ShaderNonsense();
		}
		if (ImGui::Button("Triangle"))
		{
			SetType(SHAPETYPE::TRIANGLE);
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

	inline void SetMVPUniform(glm::vec3 _position)
	{
		proj = glm::perspective(glm::radians(m_Camera->Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
		model = glm::translate(glm::mat4(1.0f), _position);
		view = m_Camera->GetViewMatrix();
		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
	}

	inline void SetMVPUniform()
	{
		proj = glm::perspective(glm::radians(m_Camera->Zoom), 1920.0f / 1080.0f, 0.1f, 100.0f);
		model = glm::translate(glm::mat4(1.0f), m_Position);
		view = m_Camera->GetViewMatrix();
		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
	}

	inline void SetCopyColour(float _r, float _g, float _b, float _a)
	{
		m_RGBA_Copy.w = _a;
		m_RGBA_Copy.x = _r;  // R
		m_RGBA_Copy.y = _g;  // G
		m_RGBA_Copy.z = _b;  // B
	}

	void CreateCopy();

	bool GetWireFrameMode()
	{
		return m_WireFrameMode;
	}
protected:
	Texture* m_Texture = nullptr;

	bool m_WireFrameMode = false;

	glm::mat4 proj = glm::perspective(45.0f, (float)1920.0f / (float)1080.0f, 0.0f, 4000.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2));
	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position);

	std::map<int, bool>* m_KeyPresses = nullptr;
	std::map<std::string, std::pair<glm::vec4, glm::vec3>> m_Copies;

	float m_dt = 0.0f;

	glm::vec3 m_Position = { 0, 0, -10 };
	float m_MovementSpeed = 2.0f;
	glm::vec4 m_RGBA_Copy = {1,0,0,1};
	float m_Color[4] = { 1,0,0,1 };

	unsigned int m_NumOfCopies = 0;

	bool m_HoldingShift = false;
	bool m_GrabCube = false;

	void Movement(float _dt)
	{
		UpdatePosition(m_InputVec.x * m_MovementSpeed * _dt, m_InputVec.y * m_MovementSpeed * _dt, m_InputVec.z * m_MovementSpeed * _dt);

		m_Copies["Cube"] = std::make_pair(glm::vec4({ m_Color[0], m_Color[1], m_Color[2], m_Color[3] }), m_Camera->Position + glm::vec3(m_Camera->Front.x * 5, m_Camera->Front.y * 5, m_Camera->Front.z * 5));
	}

	void ShaderNonsense();
	bool UpdatePosition(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);
};
