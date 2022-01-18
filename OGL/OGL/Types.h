#pragma once
#include <set>
#include <algorithm>
namespace Harmony
{


	struct BaseSystem;
	struct BaseComponent;

	const size_t MAX_ENTITY_COUNT = 1000;
	const size_t MAX_COMPONENT_COUNT = 32;

	using EntityID = size_t;
	using SystemTypeID = size_t;
	using ComponentTypeID = size_t;
	using EntitySignature = std::set<ComponentTypeID>;

	inline static const ComponentTypeID GetComponentTypeID()
	{
		static ComponentTypeID typeID = 0u;
		return typeID++;
	}

	inline static const SystemTypeID GetSystemTypeID()
	{
		static SystemTypeID typeID = 0u;
		return typeID++;
	}

	template <typename T>
	inline static const ComponentTypeID ComponentType() noexcept
	{
		static_assert((std::is_base_of<BaseComponent, T>::value && !std::is_same<BaseComponent, T>::value), "Invalid Templated Type");
		static const ComponentTypeID typeID = GetComponentTypeID();
		return typeID;
	}

	template <typename T>
	inline static const SystemTypeID SystemType() noexcept
	{
		static_assert((std::is_base_of<BaseSystem, T>::value && !std::is_same<BaseSystem, T>::value), "Invalid Templated Type");
		static const SystemTypeID typeID = GetSystemTypeID();
		return typeID;
	}
}




