#include <Castle/Systems/KinematicSystem.hpp>
#include <Castle/Components/PositionComponent.hpp>
#include <Castle/Components/CollisionComponent.hpp>
#include <Castle/Infrastructure/EntityGroups.hpp>
#include <Utility/VectorMath.hpp>

#define GRAVITATION_VEL 40.0f

namespace castle {

	KinematicSystem::KinematicSystem(void) {
		
	}

	void KinematicSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (ecs::Entity *e : _entityManager.getEntitiesByGroup(EntityGroup::GKinematic)) {
			updateEntity(e, _delta);
		}
	}
	bool KinematicSystem::handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) {
		return false;
	}

	void KinematicSystem::updateEntity(ecs::Entity* _entity, float _delta) const {
		auto& pos = _entity->getComponent<PositionComponent>();
		auto& col = _entity->getComponent<CollisionComponent>();

		pos.previousPosition = pos.position;
		pos.position += col.velocity * _delta;

		if (col.effectedByGravity && !col.isOnClimbable) {
			col.velocity.y += GRAVITATION_VEL * _delta;
		}
	}

}
