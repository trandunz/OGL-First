#include "Scene.h"
#include "Entity.h"

namespace Harmony
{
	Entity Scene::CreateEntity(std::string_view _name)
	{
		Entity entity = { m_Registy.create(), this };
		entity.AddComponent<TransformComponent>();	// Transform
		auto& tag = entity.AddComponent<TagComponent>();	// Name
		tag.Tag = _name.empty() ? "Entity" : _name;
		return entity;
	}

	void Scene::DeleteEntity(entt::entity& _entity)
	{
		m_Registy.destroy(_entity);
	}
	
}

