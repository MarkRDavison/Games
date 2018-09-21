#include <Intrusion/Systems/TowerTargetingSystem.hpp>
#include <Intrusion/Infrastructure/IntrusionEntityGroups.hpp>
#include <Intrusion/Components/TowerTargetingComponent.hpp>
#include <Intrusion/Components/PositionComponent.hpp>
#include <Utility/VectorMath.hpp>

namespace itr {
	
	TowerTargetingSystem::TowerTargetingSystem(void) {
		
	}
	TowerTargetingSystem::~TowerTargetingSystem(void) {
		
	}

	void TowerTargetingSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (ecs::Entity *_entity : _entityManager.getEntitiesByGroup(EntityGroup::GTower)) {
			updateEntity(_entity, _delta, _entityManager);
		}
	}

	void TowerTargetingSystem::updateEntity(ecs::Entity* _entity, float _delta, ecs::EntityManager& _entityManager) {
		TowerTargetingComponent& ttc = _entity->getComponent<TowerTargetingComponent>();
		PositionComponent& pc = _entity->getComponent<PositionComponent>();
		if (!ttc.target.expired()) {
			if (targetStillInRange(pc, ttc)) {
				return;
			}
			ttc.target.reset();
		}

		// We dont have a target, so now find the closest one, for now, maybe different towers can have different targeting strategies.
		const std::vector<ecs::Entity *>& targets = _entityManager.getEntitiesByGroup(EntityGroup::GTowerTarget);

		if (targets.empty()) {
			return;
		}

		const auto closest = std::min_element(targets.begin(), targets.end(), [&](ecs::Entity *_first, ecs::Entity *_second) {
			PositionComponent& pc1 = _first->getComponent<PositionComponent>();
			PositionComponent& pc2 = _second->getComponent<PositionComponent>();

			return inf::VectorMath::lengthSquared(pc.position - pc1.position) < inf::VectorMath::lengthSquared(pc.position - pc2.position);
		});

		if (closest == targets.end()) {
			return;
		}

		ecs::Entity *potentialTarget = *closest;
		PositionComponent& tpc = potentialTarget->getComponent<PositionComponent>();

		if (ttc.range * ttc.range >= inf::VectorMath::lengthSquared(pc.position - tpc.position)) {
			// Within range
			ttc.target = _entityManager.getWeakEntityRef(potentialTarget);
		}
	}

	bool TowerTargetingSystem::targetStillInRange(const PositionComponent& _towerPositionComponent, const TowerTargetingComponent& _towerTargetingComponent) {
		if (std::shared_ptr<ecs::Entity> target = _towerTargetingComponent.target.lock()) {
			const PositionComponent& targetPositionComponent = target->getComponent<PositionComponent>();
			return _towerTargetingComponent.range * _towerTargetingComponent.range >= inf::VectorMath::lengthSquared(_towerPositionComponent.position - targetPositionComponent.position);
		}
	}

}
