#ifndef INCLUDED_HURRICANE_COMPONENTS_MOVEMENT_COMPONENT_HPP_
#define INCLUDED_HURRICANE_COMPONENTS_MOVEMENT_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>
#include <SFML/System/Vector2.hpp>

namespace hur {
	struct MovementComponent : ecs::Component {
		sf::Vector2f velocity;
	};
}

#endif // INCLUDED_HURRICANE_COMPONENTS_MOVEMENT_COMPONENT_HPP_