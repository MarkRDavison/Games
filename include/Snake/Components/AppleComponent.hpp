#ifndef INCLUDED_SNAKE_COMPONENTS_APPLE_COMPONENT_HPP_
#define INCLUDED_SNAKE_COMPONENTS_APPLE_COMPONENT_HPP_

#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/Component.hpp>

namespace snake {
	
	struct AppleComponent : ecs::Component {
		int points{ 1 };
		int growth{ 1 };
		float speedup{ 1.0f };
	};

}

#endif // INCLUDED_SNAKE_COMPONENTS_APPLE_COMPONENT_HPP_