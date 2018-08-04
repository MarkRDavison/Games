#include <Hurricane/Systems/KinematicSystem.hpp>
#include <Hurricane/Infrastructure/EntityGroups.hpp>
#include <Hurricane/Components/PlayerComponent.hpp>
#include <Hurricane/Components/PositionComponent.hpp>
#include <Hurricane/Components/MovementComponent.hpp>

namespace hur {

	void KinematicSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (ecs::Entity *e : _entityManager.getEntitiesByGroup(hurr::EntityGroup::GKinematic)) {
			updateEntity(e, _delta);
		}		
	}
	bool KinematicSystem::handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) {
		return false;
	}

	void KinematicSystem::updateEntity(ecs::Entity* _entity, float _delta) const {
		MovementComponent& mc = _entity->getComponent<MovementComponent>(); // TODO: Must be movement component
		PositionComponent& pc = _entity->getComponent<PositionComponent>();

		pc.previousPosition = pc.position;

		pc.position += mc.velocity * _delta;
	}
}
