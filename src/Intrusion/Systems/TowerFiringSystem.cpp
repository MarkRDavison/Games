#include <Intrusion/Systems/TowerFiringSystem.hpp>
#include <Intrusion/Infrastructure/IntrusionEntityGroups.hpp>
#include <Intrusion/Components/TowerTargetingComponent.hpp>
#include <Intrusion/Components/TowerFiringComponent.hpp>

namespace itr {

	TowerFiringSystem::TowerFiringSystem(void) {

	}
	TowerFiringSystem::~TowerFiringSystem(void) {

	}

	void TowerFiringSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (ecs::Entity *_entity : _entityManager.getEntitiesByGroup(EntityGroup::GTower)) {
			updateEntity(_entity, _delta, _entityManager);
		}
	}

	void TowerFiringSystem::updateEntity(ecs::Entity* _entity, float _delta, ecs::EntityManager& _entityManager) {
		TowerTargetingComponent& ttc = _entity->getComponent<TowerTargetingComponent>();
		TowerFiringComponent& tfc = _entity->getComponent<TowerFiringComponent>();

		tfc.accumulatedFiringCooldown += _delta;
		if (tfc.accumulatedFiringCooldown >= tfc.firingCooldown) {
			tfc.accumulatedFiringCooldown = tfc.firingCooldown;
		} else {
			return;
		}

		if (ttc.target.expired()) {
			return;
		}

		if (std::shared_ptr<ecs::Entity> target = ttc.target.lock()) {
			tfc.accumulatedFiringCooldown = 0.0f;
			if (projectileSpawned) {
				projectileSpawned(tfc.projectilePrototype, _entity, target.get());
			}
		}
	}

}
