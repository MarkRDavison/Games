#include <Hurricane/Systems/CollisionSystem.hpp>
#include <Hurricane/Infrastructure/EntityGroups.hpp>

namespace hur {

	void CollisionSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (ecs::Entity *e : _entityManager.getEntitiesByGroup(hurr::EntityGroup::GCollideable)) {
			updateEntity(e, _delta);
		}
	}
	bool CollisionSystem::handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) {
		return false;
	}

	void CollisionSystem::updateEntity(ecs::Entity* _entity, float _delta) const {

	}
}
