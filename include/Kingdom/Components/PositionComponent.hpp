#ifndef INCLUDED_KINGDOM_COMPONENTS_POSITION_COMPONENT_HPP_
#define INCLUDED_KINGDOM_COMPONENTS_POSITION_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>

namespace kdm {
	struct PositionComponent : ecs::Component {

		PositionComponent() = default;
		PositionComponent(const sf::Vector2f& _position) : 
			position{ _position },
			previousPosition{ _position } {

		}

		sf::Vector2f position;
		sf::Vector2f previousPosition;
	};
}

#endif // INCLUDED_KINGDOM_COMPONENTS_POSITION_COMPONENT_HPP_