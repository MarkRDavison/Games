#include <Hurricane/Systems/PickupControlSystem.hpp>
#include <Hurricane/Infrastructure/EntityGroups.hpp>
#include <Hurricane/Components/PositionComponent.hpp>
#include <Hurricane/Components/PickupComponent.hpp>
#include <Hurricane/Components/HealthComponent.hpp>
#include <iostream>

namespace hur {

	void PickupControlSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (ecs::Entity *e : _entityManager.getEntitiesByGroup(hurr::EntityGroup::GPickup)) {
			updateEntity(e, _entityManager);
		}
	}
	bool PickupControlSystem::handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) {
		return false;
	}

	void PickupControlSystem::updateEntity(ecs::Entity* _entity, ecs::EntityManager& _entityManager) const {
		PickupComponent& puc = _entity->getComponent<PickupComponent>();

		if (puc.pickedUpEntity != nullptr) {
			handleEntityPickingUpPickup(puc.pickedUpEntity, puc, _entityManager);
			_entity->destroy();
			return;
		}

		const float pos = _entity->getComponent<PositionComponent>().position.y;
		if (pos > 20.0f) { // TODO: Out of bounds checking etc etc, Movement system marks them as out of view?????
			_entity->destroy();
			return;
		}
	}

	void PickupControlSystem::handleEntityPickingUpPickup(ecs::Entity* _pickingUpEntity, PickupComponent _pickup, ecs::EntityManager& _entityManager) const {
		if (_pickup.effect == PickupEffect::Health ||
			_pickup.effect == PickupEffect::Armour || 
			_pickup.effect == PickupEffect::Shields) {

			std::string healthComponent = _pickup.effect == PickupEffect::Health ? "Health" : (_pickup.effect == PickupEffect::Armour ? "Armour" : "Shields");

			std::cout << "Applying " << _pickup.integerAmount << " " << healthComponent << " to " << _pickingUpEntity->name << std::endl;

			if (_pickingUpEntity->hasComponent<HealthComponent>()) {
				HealthComponent& hc = _pickingUpEntity->getComponent<HealthComponent>();
				if (_pickup.effect == PickupEffect::Health) {
					hc.health += _pickup.integerAmount;
					if (hc.health > hc.maxHealth) {
						hc.health = hc.maxHealth;
					}
					std::cout << _pickingUpEntity->name << " now has " << hc.health << "/" << hc.maxHealth << std::endl;
				}

				if (_pickup.effect == PickupEffect::Armour) {
					hc.armour += _pickup.integerAmount;
					if (hc.armour > hc.maxArmour) {
						hc.armour = hc.maxArmour;
					}
					std::cout << _pickingUpEntity->name << " now has " << hc.armour << "/" << hc.maxArmour << std::endl;
				}

				if (_pickup.effect == PickupEffect::Shields) {
					hc.shields += _pickup.integerAmount;
					if (hc.shields > hc.maxShields) {
						hc.shields = hc.maxShields;
					}
					std::cout << _pickingUpEntity->name << " now has " << hc.shields << "/" << hc.maxShields << std::endl;
				}

			}
		}
	}

}
