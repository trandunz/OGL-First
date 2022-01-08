#pragma once
#include "CShape.h"
#include "GUI.h"

class CSquare : public CShape
{
public:
	CSquare(std::map<int,bool>& _keyMap);
    virtual ~CSquare();
    void Start();
	void CursorEnterCallback(GLFWwindow* window, int entered);
    void Input(GLFWwindow* window, int key, int scancode, int action, int mods);
	void Update(long double& _dt);
    void Render();
	void ImGuiHandler()
	{
		if (ImGui::Button("WireFrame Mode"))
		{
			m_WireFrameMode = !m_WireFrameMode;
			ShaderNonsense();
		}
		if (ImGui::Button("Red"))
		{
			SetColour(1, 0, 0, 1);
		}
		if (ImGui::Button("Blue"))
		{
			SetColour(0, 0, 1, 1);
		}
		if (ImGui::Button("Green"))
		{
			SetColour(0, 1, 0, 1);
		}
		if (ImGui::Button("Square"))
		{
			SetType(SHAPETYPE::SQUARE);
			ShaderNonsense();
		}
		if (ImGui::Button("Triangle"))
		{
			SetType(SHAPETYPE::TRIANGLE);
			ShaderNonsense();
		}
	}

	inline void SetMVPUniform()
	{
		model = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
	}

	inline void SetColour(float _r, float _g, float _b, float _a)
	{
		m_RGBA.w = _a;
		m_RGBA.x = _r;  // R
		m_RGBA.y = _g;  // G
		m_RGBA.z = _b;  // B
	}
protected:

	Texture* m_Texture = nullptr;

	bool m_WireFrameMode = false;
	bool m_DuplicateOnSwitch = false;

	glm::mat4 proj = glm::perspective(45.0f, (float)1920.0f / (float)1080.0f, 0.0f, 4000.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -1));
	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position);

	std::map<int, bool>* m_KeyPresses = nullptr;

	float m_dt = 0.0f;

	glm::vec3 m_Position = { 0, 0, 0 };
	float m_MovementSpeed = 2.0f;

	glm::vec4 m_RGBA = {1,0,0,1};

	void Movement(float _dt)
	{
		UpdatePosition(m_InputVec.x * m_MovementSpeed * _dt, m_InputVec.y * m_MovementSpeed * _dt, m_InputVec.z * m_MovementSpeed * _dt);
	}

	void ShaderNonsense();
	bool UpdatePosition(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);
};
