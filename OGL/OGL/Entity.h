#pragma once

#ifndef ENTITY_H
#define ENTITY_H
#include "Includes.h"
#include "Scene.h"

namespace Harmony
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity _handle, Scene* _scene);
		Entity(const Entity& _other) = default; // Copy Contruct
		~Entity()
		{
			m_EntityHandle = entt::null;
			m_Scene = nullptr;
		}
		bool IsAlive()
		{
			return m_Scene->m_Registy.valid(m_EntityHandle);
		}
		void Destory()
		{
			auto view = m_Scene->m_Registy.view<MeshComponent>();
			m_Scene->m_Registy.destroy(m_EntityHandle);
			NEW = true;
		}
		template <typename T, typename... Args>
		T& AddComponent(Args&&... _args)
		{
			NEW = false;
			return m_Scene->m_Registy.emplace<T>(m_EntityHandle, std::forward<Args>(_args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Scene->m_Registy.get<T>(m_EntityHandle);
		}

		template <typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registy.any_of<T>(m_EntityHandle);
		}

		template <typename T>
		void RemoveComponent()
		{
			if (HasComponent<T>())
				m_Scene->m_Registy.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const { return m_EntityHandle; }
		bool NEW = true;
	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;
	};
}
#endif

