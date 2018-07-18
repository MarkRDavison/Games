#ifndef INCLUDED_CASTLE_COMPONENTS_WAYPOINT_COMPONENT_HPP_
#define INCLUDED_CASTLE_COMPONENTS_WAYPOINT_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>

namespace castle {

	struct WaypointComponent : ecs::Component {
		std::vector<std::pair<sf::Vector2f, float>> waypoints;
		std::size_t currentWaypoint{0u};
	};
	
}

#endif // INCLUDED_CASTLE_COMPONENTS_WAYPOINT_COMPONENT_HPP_