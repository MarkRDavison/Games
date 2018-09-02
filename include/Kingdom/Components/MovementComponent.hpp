#ifndef INCLUDED_KINGDOM_COMPONENTS_MOVEMENT_COMPONENT_HPP_
#define INCLUDED_KINGDOM_COMPONENTS_MOVEMENT_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>
#include <SFML/System/Vector2.hpp>

namespace kdm {
	struct MovementComponent : ecs::Component {
		bool targetMode{ false };
		sf::Vector2f target;
		sf::Vector2f velocity;
		float speed{0.0f};
	};
}

#endif // INCLUDED_KINGDOM_COMPONENTS_MOVEMENT_COMPONENT_HPP_