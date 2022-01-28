#include "Entity.h"

namespace Harmony
{
	Entity::Entity(entt::entity _handle, Scene* _scene)
	{
		m_EntityHandle = _handle;
		m_Scene = _scene;
	}
}

