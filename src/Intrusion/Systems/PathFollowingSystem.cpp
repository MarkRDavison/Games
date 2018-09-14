#include <Intrusion/Systems/PathFollowingSystem.hpp>
#include <Intrusion/Infrastructure/IntrusionEntityGroups.hpp>
#include <Intrusion/Components/PathFollowComponent.hpp>
#include <Intrusion/Components/PositionComponent.hpp>
#include <Utility/VectorMath.hpp>

namespace itr {

	void PathFollowingSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (ecs::Entity *e : _entityManager.getEntitiesByGroup(EntityGroup::GPathFollower)) {
			updateEntity(_delta, e, _entityManager);
		}
	}

	void PathFollowingSystem::updateEntity(float _delta, ecs::Entity* _entity, ecs::EntityManager& _entityManager) const {
		PathFollowComponent& pfc = _entity->getComponent<PathFollowComponent>();
		PositionComponent& pc = _entity->getComponent<PositionComponent>();

		if (pfc.pathPoints.empty()) {
			_entity->destroy(); // TODO: Temporary, need to figure out points and stuff, another system, watches for reaching the end???
			return;
		}

		const sf::Vector2f& target = pfc.pathPoints.front();

		const float distanceToTarget = inf::VectorMath::distance(pc.position, target);
		const float maxMovement = pfc.speed * _delta;

		if (distanceToTarget <= maxMovement) {
			pfc.pathPoints.pop();
			pc.position = target;

			const float remainingDelta = _delta - _delta * (distanceToTarget / maxMovement);

			updateEntity(remainingDelta, _entity, _entityManager);
		} else {
			pc.position += inf::VectorMath::normalise(target - pc.position) * maxMovement;
		}

	}

}
