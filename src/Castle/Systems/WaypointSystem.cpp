#include <Castle/Systems/WaypointSystem.hpp>
#include <Castle/Infrastructure/EntityGroups.hpp>
#include <Castle/Components/WaypointComponent.hpp>
#include <Castle/Components/CollisionComponent.hpp>
#include <Utility/VectorMath.hpp>

namespace castle {

	WaypointSystem::WaypointSystem(void)  {
		
	}

	void WaypointSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		auto& ens = _entityManager.getEntitiesByGroup(EntityGroup::GWaypoint);
		for (ecs::Entity *e : ens) {
			updateEntity(e, _delta);
		}
	}
	bool WaypointSystem::handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) {
		return false;
	}

	void WaypointSystem::updateEntity(ecs::Entity* _entity, float _delta) const {
		WaypointComponent& wc = _entity->getComponent<WaypointComponent>();
		CollisionComponent& cc = _entity->getComponent<CollisionComponent>();
		PositionComponent& pc = _entity->getComponent<PositionComponent>();

		if (wc.waypoints.size() == 0) {
			return;
		}

		const auto& waypoint = wc.waypoints[wc.currentWaypoint];
		const float distanceToTarget = inf::VectorMath::distance(waypoint.first, pc.position);
		const float availableDistance = waypoint.second;
		const sf::Vector2f direction = inf::VectorMath::normalise(waypoint.first - pc.position);


		if (distanceToTarget > availableDistance * _delta) {
			cc.velocity = direction * availableDistance;
			return;
		}

		if (distanceToTarget != 0.0f) {
			cc.velocity = direction * availableDistance;
		}
		++wc.currentWaypoint;
		if (wc.currentWaypoint >= wc.waypoints.size()) {
			wc.currentWaypoint = 0u;
		}
	}

}
