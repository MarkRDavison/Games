#ifndef INCLUDED_KINGDOM_COMPONENTS_WAYPOINT_COMPONENT_HPP_
#define INCLUDED_KINGDOM_COMPONENTS_WAYPOINT_COMPONENT_HPP_

#include <EntityComponentSystem/Entity.hpp>

namespace kdm {
	
	struct WaypointComponent : ecs::Component {
		bool repeat{ false };
		unsigned currentWaypointIndex{ 0 };
		std::vector<sf::Vector2f> waypoints;
	};

}

#endif // INCLUDED_KINGDOM_COMPONENTS_WAYPOINT_COMPONENT_HPP_