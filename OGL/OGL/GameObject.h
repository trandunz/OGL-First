#pragma once
#include "NumptyBehavior.h"
#include "Mesh.h"
class GameObject : public NumptyBehavior
{
public:
	GameObject(Camera& _camera, TextureMaster& _textMaster, double& _dt, std::map<int, bool>& _keymap);
	~GameObject();

	void Start();
	void Update();
	void Input();
	
	Mesh& GetMesh();

	STransform Transform;
	bool MarkAsDestroy = false;
private:
	std::map<int, bool>* m_KeyMap = nullptr;
	TextureMaster* m_TextureMaster = nullptr;
	Camera* m_Camera = nullptr;
	Mesh* m_Mesh = nullptr;
	double* m_Dt = nullptr;

	void Render();
};

