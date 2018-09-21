#include <Intrusion/Systems/LifeSystem.hpp>
#include <Intrusion/Infrastructure/IntrusionEntityGroups.hpp>
#include <Intrusion/Infrastructure/IntrusionDefinitions.hpp>
#include <Intrusion/Components/LifeComponent.hpp>

namespace itr {

	LifeSystem::LifeSystem(ILevelResourceService& _levelResourceService) :
		m_LevelResourceService(_levelResourceService) {
		
	}
	LifeSystem::~LifeSystem(void) {
		
	}

	void LifeSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (ecs::Entity *_entity : _entityManager.getEntitiesByGroup(EntityGroup::GLife)) {
			updateEntity(_entity, _delta, _entityManager);
		}
	}

	void LifeSystem::updateEntity(ecs::Entity* _entity, float _delta, ecs::EntityManager& _entityManager) const {
		LifeComponent& lc = _entity->getComponent<LifeComponent>();
		if (lc.health > 0.0f) {
			while (!lc.lifeAdjustments.empty()) {
				const LifeBundle& lb = lc.lifeAdjustments.front();
				lc.lifeAdjustments.pop();

				lc.health += lb.health;
				lc.armour += lb.armour;
				lc.shields += lb.shields;
			}
		}

		if (lc.health <= 0.0f) {
			m_LevelResourceService.updateResource(Definitions::KillsResourceName, 1);
			m_LevelResourceService.receiveResourceBundle(lc.onDeathResources);
			_entity->destroy();
		}
	}

}
