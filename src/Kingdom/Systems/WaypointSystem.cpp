#include <Kingdom/Systems/WaypointSystem.hpp>
#include <Kingdom/Infrastructure/KingdomEntityGroups.hpp>
#include <Kingdom/Components/WaypointComponent.hpp>
#include <Kingdom/Components/MovementComponent.hpp>
#include <Kingdom/Components/PositionComponent.hpp>
#include <Utility/VectorMath.hpp>
#include <iostream>

namespace kdm {

	WaypointSytem::WaypointSytem(void) {
		
	}
	WaypointSytem::~WaypointSytem(void) {
		
	}

	void WaypointSytem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (const auto& _e : _entityManager.getEntitiesByGroup(kdm::EntityGroup::GWaypoint)) {
			updateEntity(_e, _delta);
		}		
	}

	void WaypointSytem::updateEntity(ecs::Entity* const _entity, float _delta) const {
		WaypointComponent& wc = _entity->getComponent<WaypointComponent>();
		MovementComponent& mc = _entity->getComponent<MovementComponent>();
		PositionComponent& pc = _entity->getComponent<PositionComponent>();
		
		if (wc.waypoints.empty()) {
			return;
		}

		if (wc.currentWaypointIndex >= wc.waypoints.size()) {
			wc.currentWaypointIndex = 0;
			if (!wc.repeat) {
				wc.waypoints.clear();
				return;
			}
		}

		const sf::Vector2f& currentWaypoint = wc.waypoints[wc.currentWaypointIndex];
		
		const float distanceToTarget = inf::VectorMath::distance(currentWaypoint, pc.position);

		if (distanceToTarget == 0.0f) {
			wc.currentWaypointIndex++;
			mc.velocity = {};
			mc.target = {};
			mc.targetMode = false;
			if (wc.waypoints.size() > 1) {
				updateEntity(_entity, _delta);
			}
			return;
		}

		mc.velocity = {};
		mc.target = currentWaypoint;
		mc.targetMode = true;

	}

}
