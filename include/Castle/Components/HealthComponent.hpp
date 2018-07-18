#ifndef INCLUDED_CASTLE_COMPONENTS_HEALTH_COMPONENT_HPP_
#define INCLUDED_CASTLE_COMPONENTS_HEALTH_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>
#include <EntityComponentSystem/Entity.hpp>

namespace castle {
	
	struct HealthComponent : ecs::Component {
		int maxHealth;
		int health;
		float currentDamageCooldown{ 0.0f };
		float damageCooldown{ 0.0f };

		HealthComponent(int _maxHealth, int _startingHealth) :
			HealthComponent(_maxHealth, _startingHealth, 1.0f) {

		}
		HealthComponent(int _maxHealth, int _startingHealth, float _damageCooldown) :
			maxHealth(_maxHealth),
			health(_startingHealth),
			currentDamageCooldown(0.0f),
			damageCooldown(_damageCooldown) {

		}

		void update(float _delta) override {
			if (currentDamageCooldown > 0.0f) {
				currentDamageCooldown -= _delta;
			}
		}
	};

}

#endif // INCLUDED_CASTLE_COMPONENTS_HEALTH_COMPONENT_HPP_