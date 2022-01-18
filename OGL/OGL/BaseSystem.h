#pragma once
#include "Types.h"

namespace Harmony
{
	class BaseSystem
	{
	public:
		BaseSystem() = default;
		virtual ~BaseSystem() = default;

		void AddEntity(const EntityID entity)
		{
			entities.insert(entity);
		}
		void RemoveEntity(const EntityID entity)
		{
			entities.erase(entity);
		}

		const EntitySignature GetSignature() const{ return signature; }

		template <typename T>
		void AddComponentSignature()
		{
			signature.insert(ComponentType<T>());
		}

	protected:
		friend class Manager;
		std::set<EntityID> entities;
		EntitySignature signature;
	};
}


