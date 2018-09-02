#ifndef INCLUDED_HURRICANE_COMPONENTS_PROJECTILE_COMPONENT_HPP_
#define INCLUDED_HURRICANE_COMPONENTS_PROJECTILE_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>

namespace hur {

	struct ProjectileComponent : ecs::Component {

		bool destroyedOnCollision{ false };

		ProjectileComponent(bool _destroyedOnCollision) :
			destroyedOnCollision(_destroyedOnCollision) {
			
		}
	};
}

#endif // INCLUDED_HURRICANE_COMPONENTS_PROJECTILE_COMPONENT_HPP_