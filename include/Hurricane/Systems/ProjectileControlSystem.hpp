#ifndef INCLUDED_HURRICANE_SYSTEMS_PROJECTILE_CONTROL_SYSTEM_HPP_
#define INCLUDED_HURRICANE_SYSTEMS_PROJECTILE_CONTROL_SYSTEM_HPP_

#include <EntityComponentSystem/System.hpp>

namespace hur {

	class ProjectileControlSystem : public ecs::System {
	public:
		void update(float _delta, ecs::EntityManager& _entityManager) override;
		bool handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) override;

		void updateEntity(ecs::Entity* _entity, ecs::EntityManager& _entityManager) const;

	};
	
}

#endif // INCLUDED_HURRICANE_SYSTEMS_PROJECTILE_CONTROL_SYSTEM_HPP_