#include <Kingdom/Systems/MovementSystem.hpp>
#include <Kingdom/Components/PositionComponent.hpp>
#include <Kingdom/Components/MovementComponent.hpp>
#include <Kingdom/Infrastructure/KingdomEntityGroups.hpp>
#include <Utility/VectorMath.hpp>

namespace kdm {

	MovementSystem::MovementSystem(void) {

	}
	MovementSystem::~MovementSystem(void) {

	}

	void MovementSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (const auto& _e : _entityManager.getEntitiesByGroup(kdm::EntityGroup::GMoveable)) {
			updateEntity(_e, _delta);
		}
	}

	void MovementSystem::updateEntity(ecs::Entity* const _entity, float _delta) const {
		PositionComponent& pc = _entity->getComponent<PositionComponent>();
		MovementComponent& mc = _entity->getComponent<MovementComponent>();

		pc.previousPosition = pc.position;

		if (mc.targetMode) {
			const float distanceToTarget = inf::VectorMath::distance(pc.position, mc.target);
			sf::Vector2f orientationToTarget = mc.target - pc.position;
			inf::VectorMath::normalise(orientationToTarget);

			if (distanceToTarget <= mc.speed * _delta) {
				pc.position = mc.target;
				mc.targetMode = false;
				mc.target = {};
			} else {
				pc.position += orientationToTarget * mc.speed * _delta;
			}
		} else {
			pc.position += mc.velocity * _delta;
		}		
	}

}
