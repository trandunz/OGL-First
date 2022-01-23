#pragma once
#include "CShape.h"
#include "GUI.h"
#include "Physics.h"

namespace Shape
{
	class CSquare : public CShape
	{
	public:
		CSquare(std::map<int, bool>& _keyMap, Camera& _camera);
		virtual ~CSquare();

		void CursorEnterCallback(GLFWwindow* window, int entered);
		void Input(glm::vec3 _mouseRay, GLFWwindow* window, int key, int scancode, int action, int mods);
		void Update(long double& _dt);
	protected:
		Texture* m_Texture = nullptr;
		VertexArray* m_LightCubeVAO = nullptr;

		std::map<int, bool>* m_KeyPresses = nullptr;
		std::map<std::string, std::pair<glm::vec4, STransform>> m_Copies;

		unsigned int m_NumOfCopies = 0;

		float m_MovementSpeed = 2.0f;

		bool m_HoldingShift = false;
		bool m_GrabCube = false;
		bool m_RotateX = false;
		bool m_RotateY = false;
		bool m_RotateZ = false;

		void Start();
		void InitRender(const char* _vsAddress = "Resources/Shaders/basic_lighting.vs", const char* _gsAddress = "",
			const char* _fsAddress = "Resources/Shaders/basic_lighting.fs", const char* _texAddress = "Resources/Textures/3.jpg",
			VertexBufferLayout _vbLayouts = VertexBufferLayout());
		void Render();
		void ImGuiHandler();

		void SetCopyColour(float _r, float _g, float _b, float _a);
		void CreateCopy();

		void Movement(float _dt);

		void ProcessRotationSlider();
	};
}

