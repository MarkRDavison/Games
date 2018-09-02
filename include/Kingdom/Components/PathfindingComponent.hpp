#ifndef INCLUDED_KINGDOM_COMPONENTS_PATHFINDING_COMPONENT_HPP_
#define INCLUDED_KINGDOM_COMPONENTS_PATHFINDING_COMPONENT_HPP_

#include <EntityComponentSystem/Entity.hpp>

namespace kdm {
	
	struct PathfindingComponent : ecs::Component {
		bool pathRequested{ false };
		bool pathAttempedButFailed{ false };
		sf::Vector2u start; 
		sf::Vector2u end;
	};

}

#endif // INCLUDED_KINGDOM_COMPONENTS_PATHFINDING_COMPONENT_HPP_