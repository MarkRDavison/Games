#ifndef INCLUDED_ARKANOID_COMPONENTS_POSITION_COMPONENT_HPP_
#define INCLUDED_ARKANOID_COMPONENTS_POSITION_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>

namespace ark {
	struct PositionComponent : ecs::Component {

		PositionComponent() = default;
		PositionComponent(const sf::Vector2f& _position) : position{ _position } {
			
		}

		float x() const noexcept { return position.x; }
		float y() const noexcept { return position.y; }

		sf::Vector2f position;
	};
}

#endif // INCLUDED_ARKANOID_COMPONENTS_POSITION_COMPONENT_HPP_