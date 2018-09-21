#include <Intrusion/Systems/ProjectileControlSystem.hpp>
#include <Intrusion/Infrastructure/IntrusionEntityGroups.hpp>
#include <Intrusion/Components/ProjectileComponent.hpp>
#include <Intrusion/Components/PathFollowComponent.hpp>
#include <Intrusion/Components/PositionComponent.hpp>

namespace itr {
	
	ProjectileControlSystem::ProjectileControlSystem(void) {
		
	}
	ProjectileControlSystem::~ProjectileControlSystem(void) {
		
	}

	void ProjectileControlSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (ecs::Entity *_entity : _entityManager.getEntitiesByGroup(EntityGroup::GProjectile)) {
			updateEntity(_entity, _delta, _entityManager);
		}
	}

	void ProjectileControlSystem::updateEntity(ecs::Entity* _entity, float _delta, ecs::EntityManager& _entityManager) {
		ProjectileComponent& pc = _entity->getComponent<ProjectileComponent>();
		PathFollowComponent& pfc = _entity->getComponent<PathFollowComponent>();

		if (std::shared_ptr<ecs::Entity> target = pc.target.lock()) {
			if (!pfc.pathPoints.empty()) {
				const sf::Vector2f targetPosition = target->getComponent<PositionComponent>().position;
				pfc.pathPoints.back().x = targetPosition.x;
				pfc.pathPoints.back().y = targetPosition.y;
			}
		}
	}

}
