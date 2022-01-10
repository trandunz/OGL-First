#pragma once
#include "CShape.h"
#include "GUI.h"

struct PointLight {
	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class CSquare : public CShape
{
public:
	CSquare();
	CSquare(std::map<int,bool>& _keyMap, Camera& _camera);
    virtual ~CSquare();
    virtual void Start();
	virtual void CursorEnterCallback(GLFWwindow* window, int entered);
	virtual void Input(GLFWwindow* window, int key, int scancode, int action, int mods);
	virtual void Update(long double& _dt);
	virtual void Render();
	virtual void ImGuiHandler()
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
	VertexArray* m_LightCubeVAO = nullptr;

	bool m_WireFrameMode = false;

	std::map<int, bool>* m_KeyPresses = nullptr;
	std::map<std::string, std::pair<glm::vec4, glm::vec3>> m_Copies;

	PointLight m_PointLights[10];

	unsigned int m_NumOfCopies = 0;

	float m_MovementSpeed = 2.0f;

	bool m_HoldingShift = false;
	bool m_GrabCube = false;

	void Movement(float _dt)
	{
		UpdatePosition(m_InputVec.x * m_MovementSpeed * _dt, m_InputVec.y * m_MovementSpeed * _dt, m_InputVec.z * m_MovementSpeed * _dt);

		m_Copies["0"] = std::make_pair(glm::vec4({ m_Color[0], m_Color[1], m_Color[2], m_Color[3] }), m_Position);
	}

	void ShaderNonsense();
	bool UpdatePosition(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);
};
