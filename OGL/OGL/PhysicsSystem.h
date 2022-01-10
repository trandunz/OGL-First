#include "Coordinator.h"

struct Gravity
{
	glm::vec3 force;
};

struct RigidBody
{
	glm::vec3 velocity;
	glm::vec3 acceleration;
};

extern Coordinator gCoordinator;

class PhysicsSystem
{
public:

	PhysicsSystem() {};
	void Update(float dt)
	{
		for (auto const& entity : m_Entities)
		{
			auto& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
			auto& transform = gCoordinator.GetComponent<Transform>(entity);
			auto const& gravity = gCoordinator.GetComponent<Gravity>(entity);

			transform.position += rigidBody.velocity * dt;

			rigidBody.velocity += gravity.force * dt;
		}
	}

	std::vector<Entity> m_Entities;
};



