#pragma once
#include "Types.h"

namespace Harmony
{
	struct BaseComponent
	{
	public:
		BaseComponent() : entityID() {}
		virtual ~BaseComponent() {}
		inline const EntityID GetID() const { return entityID; }

	private:
		friend class Manager;
		EntityID entityID;
	};
}

