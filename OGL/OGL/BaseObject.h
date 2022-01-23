#pragma once
#include "NumptyBehavior.h"
#include "Mesh.h"

class BaseObject : public NumptyBehavior
{
public:
	void AddMesh();
	void RemoveMesh();
private:
	Camera* m_Camera = nullptr;
	Mesh* m_Mesh = nullptr;
};

