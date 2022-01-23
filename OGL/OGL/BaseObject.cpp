#include "BaseObject.h"

void BaseObject::AddMesh()
{
	if (!m_Mesh)
		m_Mesh = new Mesh(*m_Camera);
}

void BaseObject::RemoveMesh()
{
	CleanupPointer(m_Mesh);
}
