#ifndef INCLUDED_HURRICANE_COMPONENTS_HEALTH_COMPONENT_HPP_
#define INCLUDED_HURRICANE_COMPONENTS_HEALTH_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>

namespace hur {
	struct HealthComponent : ecs::Component {
		int health{ 0 };
		int maxHealth{ 0 };
		int armour{ 0 };
		int maxArmour{ 0 };
		int shields{ 0 };
		int maxShields{ 0 };
		int teamNumber{ 0 };

		HealthComponent(int _health, int _maxHealth, int _teamNumber) :
			health(_health),
			maxHealth(_maxHealth),
			teamNumber(_teamNumber) {
			
		}
	};
}

#endif // INCLUDED_HURRICANE_COMPONENTS_HEALTH_COMPONENT_HPP_