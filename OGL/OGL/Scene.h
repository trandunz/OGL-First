#pragma once
#include <string>
#include <entt/entt.hpp>
#include "Components.h"

namespace Harmony
{
	class Entity;
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity(const std::string _name = {});
		void DeleteEntity(entt::entity& _entity);
	private:
		friend class Entity;
		entt::registry m_Registy;
	};
}


