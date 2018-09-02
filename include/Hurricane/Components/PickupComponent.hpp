#ifndef INCLUDED_HURRICANE_COMPONENTS_PICKUP_COMPONENT_HPP_
#define INCLUDED_HURRICANE_COMPONENTS_PICKUP_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>

namespace hur {

	enum class PickupEffect {
		Health,
		Shields,
		Armour,

		None
	};

	struct PickupComponent : ecs::Component {
		ecs::Entity *pickedUpEntity{ nullptr };
		PickupEffect effect{ PickupEffect::None };
		int integerAmount{ 0 };

	};
}

#endif // INCLUDED_HURRICANE_COMPONENTS_PICKUP_COMPONENT_HPP_