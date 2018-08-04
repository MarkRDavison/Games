#include <Hurricane/Systems/ProjectileControlSystem.hpp>
#include <Hurricane/Infrastructure/EntityGroups.hpp>
#include <Hurricane/Components/PositionComponent.hpp>

namespace hur {

	void ProjectileControlSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (ecs::Entity *e : _entityManager.getEntitiesByGroup(hurr::EntityGroup::GProjectile)) {
			updateEntity(e, _entityManager);
		}
	}
	bool ProjectileControlSystem::handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) {
		return false;
	}

	void ProjectileControlSystem::updateEntity(ecs::Entity* _entity, ecs::EntityManager& _entityManager) const {
		if (_entity->getComponent<PositionComponent>().position.y < 0.0f) {
			_entity->destroy();
		}
	}

}
