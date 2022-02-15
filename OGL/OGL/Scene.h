#pragma once
#include "Includes.h"
#include "Components.h"

namespace Harmony
{
	class Entity;
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity(std::string_view _name = {});

		entt::registry& GetReg() { return m_Registy; }
		void DeleteEntity(entt::entity& _entity);
	private:
		friend class Entity;
		entt::registry m_Registy;
	};
}


