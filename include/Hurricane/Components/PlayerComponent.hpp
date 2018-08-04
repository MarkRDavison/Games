#ifndef INCLUDED_HURRICANE_COMPONENTS_PLAYER_COMPONENT_HPP_
#define INCLUDED_HURRICANE_COMPONENTS_PLAYER_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>

namespace hur {
	struct PlayerComponent : ecs::Component {

		sf::Vector2f direction;

		const float speed {8.0f};
		bool canFire{ false };
	};
}

#endif // INCLUDED_HURRICANE_COMPONENTS_PLAYER_COMPONENT_HPP_