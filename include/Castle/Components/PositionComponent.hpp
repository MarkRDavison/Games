#ifndef INCLUDED_CASTLE_COMPONENTS_POSITION_COMPONENT_HPP_
#define INCLUDED_CASTLE_COMPONENTS_POSITION_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>

namespace castle {
	struct PositionComponent : ecs::Component {

		PositionComponent() = default;
		PositionComponent(const sf::Vector2f& _position) : position{ _position } {

		}

		sf::Vector2f position;
		sf::Vector2f previousPosition;
	};
}

#endif // INCLUDED_CASTLE_COMPONENTS_POSITION_COMPONENT_HPP_