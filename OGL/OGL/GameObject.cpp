#include "GameObject.h"

GameObject::GameObject(Camera& _camera, TextureMaster& _textMaster, double& _dt, std::map<int, bool>& _keymap)
{
	m_TextureMaster = &_textMaster;
	m_Camera = &_camera;
	m_Dt = &_dt;
	m_KeyMap = &_keymap;

	Start();
}

GameObject::~GameObject()
{
	CleanupPointer(m_Mesh);
	m_TextureMaster = nullptr;
	m_Camera = nullptr;
	m_Dt = nullptr;
	m_KeyMap = nullptr;
}

void GameObject::Start()
{
	CleanupPointer(m_Mesh);
	m_Mesh = new Mesh(*m_Camera,*m_TextureMaster);

	for (int i = 0; i < (int)(m_Mesh->GetInstanceMatrixSize()); i++)
	{
		m_Mesh->ModifyInstanceMatrix(i, { {0,0,0},{1,0,0},{1,1,1},45 });
	}
}

void GameObject::Update()
{
	Render();
}

void GameObject::Input()
{
	for (auto& item : (*m_KeyMap))
	{
		if (item.second == true)
		{
			switch (item.first)
			{
			default:
				break;
			}
		}
		if (item.second == false)
		{
			switch (item.first)
			{
			default:
				break;
			}
		}
	}
}

Mesh& GameObject::GetMesh()
{
	return *m_Mesh;
}

void GameObject::Render()
{ 
	m_Mesh->Draw();
}
