#ifndef INCLUDED_HURRICANE_SYSTEMS_PICKUP_CONTROL_SYSTEM_HPP_
#define INCLUDED_HURRICANE_SYSTEMS_PICKUP_CONTROL_SYSTEM_HPP_

#include <EntityComponentSystem/System.hpp>
#include <Hurricane/Components/PickupComponent.hpp>

namespace hur {

	class PickupControlSystem : public ecs::System {
	public:
		void update(float _delta, ecs::EntityManager& _entityManager) override;
		bool handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) override;

		void updateEntity(ecs::Entity* _entity, ecs::EntityManager& _entityManager) const;

		void handleEntityPickingUpPickup(ecs::Entity *_pickingUpEntity, PickupComponent _pickup, ecs::EntityManager& _entityManager) const;
	};

}

#endif // INCLUDED_HURRICANE_SYSTEMS_PICKUP_CONTROL_SYSTEM_HPP_