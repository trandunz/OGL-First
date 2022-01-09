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
		if (ImGui::Button("CreateCopy"))
		{
			m_NumOfCopies++;
			m_Copies[std::to_string(m_NumOfCopies)] = std::make_pair(m_RGBA, m_Camera->Position);
		}
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

	inline void SetColour(float _r, float _g, float _b, float _a)
	{
		m_RGBA.w = _a;
		m_RGBA.x = _r;  // R
		m_RGBA.y = _g;  // G
		m_RGBA.z = _b;  // B
	}

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

	glm::vec3 m_Position = { 0, 0, 0 };
	float m_MovementSpeed = 2.0f;
	glm::vec4 m_RGBA = {1,0,0,1};

	unsigned int m_NumOfCopies = 0;

	void Movement(float _dt)
	{
		UpdatePosition(m_InputVec.x * m_MovementSpeed * _dt, m_InputVec.y * m_MovementSpeed * _dt, m_InputVec.z * m_MovementSpeed * _dt);
		
		m_Copies["Cube"] = std::make_pair(glm::vec4(1,0,0,1), m_Position);
	}

	void ShaderNonsense();
	bool UpdatePosition(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);
};
