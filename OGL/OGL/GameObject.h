#pragma once
#include "NumptyBehavior.h"
#include "Mesh.h"

namespace Harmony
{
	class GameObject : public NumptyBehavior
	{
	public:
		GameObject(Camera& _camera, TextureMaster& _textMaster, double& _dt, std::map<int, bool>& _keymap);
		~GameObject();

		void Start();
		void Update();
		void Input();

		Mesh& GetMesh()
		{
			return *m_Mesh;
		}

		STransform Transform;
		bool MarkAsDestroy = false;
	private:
		Mesh* m_Mesh = nullptr;
		std::map<int, bool>* m_KeyMap = nullptr;
		TextureMaster* m_TextureMaster = nullptr;
		Camera* m_Camera = nullptr;
		double* m_Dt = nullptr;

		void Render();
	};
}


