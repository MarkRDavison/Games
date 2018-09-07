#include <Intrusion/Systems/PathFollowingSystem.hpp>
#include <Intrusion/Infrastructure/IntrusionEntityGroups.hpp>
#include <Intrusion/Components/PathFollowComponent.hpp>
#include <Intrusion/Components/PositionComponent.hpp>

namespace itr {

	void PathFollowingSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (ecs::Entity *e : _entityManager.getEntitiesByGroup(EntityGroup::GPathFollower)) {
			updateEntity(_delta, e, _entityManager);
		}
	}

	void PathFollowingSystem::updateEntity(float _delta, ecs::Entity* _entity, ecs::EntityManager& _entityManager) const {
		PathFollowComponent& pfc = _entity->getComponent<PathFollowComponent>();
		PositionComponent& pc = _entity->getComponent<PositionComponent>();


	}

}
