#ifndef INCLUDED_INTRUSION_COMPONENTS_TOWER_FIRING_COMPONENT_HPP_
#define INCLUDED_INTRUSION_COMPONENTS_TOWER_FIRING_COMPONENT_HPP_

#include <EntityComponentSystem/Entity.hpp>

namespace itr {

	struct TowerFiringComponent : ecs::Component {
		float accumulatedFiringCooldown{ 0.0f };
		float firingCooldown{ 0.0f };
		ParsedProjectile projectilePrototype;
	};

}

#endif // INCLUDED_INTRUSION_COMPONENTS_TOWER_FIRING_COMPONENT_HPP_