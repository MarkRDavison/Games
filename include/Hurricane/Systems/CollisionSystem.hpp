#ifndef INCLUDED_HURRICANE_SYSTEMS_COLLISION_SYSTEM_HPP_
#define INCLUDED_HURRICANE_SYSTEMS_COLLISION_SYSTEM_HPP_

#include <EntityComponentSystem/System.hpp>

namespace hur {

	class CollisionSystem : public ecs::System {
	public:
		void update(float _delta, ecs::EntityManager& _entityManager) override;
		bool handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) override;

		void updateEntity(ecs::Entity* _entity, float _delta) const;
	};
	
}

#endif // INCLUDED_HURRICANE_SYSTEMS_COLLISION_SYSTEM_HPP_