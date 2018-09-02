#include <Hurricane/Systems/CollisionSystem.hpp>
#include <Hurricane/Infrastructure/EntityGroups.hpp>
#include <Hurricane/Components/CollisionComponent.hpp>
#include <iostream>
#include <Hurricane/Components/DamageComponent.hpp>
#include <Hurricane/Components/HealthComponent.hpp>
#include <Hurricane/Components/ProjectileComponent.hpp>
#include <Hurricane/Infrastructure/Definitions.hpp>
#include <Hurricane/Components/DropComponent.hpp>
#include <Hurricane/Components/PositionComponent.hpp>
#include <Hurricane/Components/PickupComponent.hpp>
#include <Hurricane/Components/PlayerComponent.hpp>

namespace hur {

	CollisionSystem::CollisionSystem(EntityFactory& _entityFactory) :
		m_EntityFactory(_entityFactory) {
		
	}

	void CollisionSystem::update(float _delta, ecs::EntityManager& _entityManager) {

		const auto& collideableEntities = _entityManager.getEntitiesByGroup(hurr::EntityGroup::GCollideable);

		for (std::size_t i = 0; i < collideableEntities.size(); ++i) {
			ecs::Entity *entity1 = collideableEntities[i];
			CollisionComponent& cc1 = entity1->getComponent<CollisionComponent>();
			for (std::size_t j = i + 1; j < collideableEntities.size(); ++j) {
				ecs::Entity *entity2 = collideableEntities[j];
				CollisionComponent& cc2 = entity2->getComponent<CollisionComponent>();

				if (cc1.getBounds().intersects(cc2.getBounds())) {
					handleCollision(entity1, entity2, _delta, _entityManager);
				}
			}
		}
	}
	bool CollisionSystem::handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) {
		return false;
	}

	void CollisionSystem::handleCollision(ecs::Entity* _entity1, ecs::Entity* _entity2, float _delta, ecs::EntityManager& _entityManager) {
		CollisionComponent& cc1 = _entity1->getComponent<CollisionComponent>();
		CollisionComponent& cc2 = _entity2->getComponent<CollisionComponent>();

		const bool e1Damage = _entity1->hasComponent<DamageComponent>();
		const bool e2Damage = _entity2->hasComponent<DamageComponent>();

		const bool e1Health = _entity1->hasComponent<HealthComponent>();
		const bool e2Health = _entity2->hasComponent<HealthComponent>();


		if (e1Damage && e2Health) {
			// Entity 1 can damage entity 2
			handleDamaging(_entity1, _entity2, _entityManager);
		}
		if (e2Damage && e1Health) {
			// Entity 2 can damage entity 1
			handleDamaging(_entity2, _entity1, _entityManager);
		}

		const bool e1Pickup = _entity1->hasComponent<PickupComponent>();
		const bool e2Pickup = _entity2->hasComponent<PickupComponent>();

		const bool e1Player = _entity1->hasComponent<PlayerComponent>();
		const bool e2Player = _entity2->hasComponent<PlayerComponent>();

		if (e1Player && e2Pickup) {
			handlePickup(_entity1, _entity2, _entityManager);
		}
		if (e2Player && e1Pickup) {
			handlePickup(_entity2, _entity1, _entityManager);
		}
	}

	void CollisionSystem::handleDamaging(ecs::Entity* _entity1, ecs::Entity* _entity2, ecs::EntityManager& _entityManager) {
		DamageComponent& dc1 = _entity1->getComponent<DamageComponent>();
		HealthComponent& hc2 = _entity2->getComponent<HealthComponent>();

		if (hc2.teamNumber != dc1.damageTeam) {
			if (dc1.damageType == Definitions::StandardDamageType) {
				hc2.health -= dc1.damageAmount;
			}
			if (hc2.health <= 0) {
				if (_entity2->hasComponent<DropComponent>()) {
					DropComponent& dc = _entity2->getComponent<DropComponent>();
					m_EntityFactory.createPotentialDropFromDropTable(_entityManager, dc.dropTable, _entity2->getComponent<PositionComponent>().position);
				}
				_entity2->destroy();
			}
		}

		if (_entity1->hasComponent<ProjectileComponent>()) {
			if (_entity1->getComponent<ProjectileComponent>().destroyedOnCollision) {
				_entity1->destroy();
			}
		}
	}

	void CollisionSystem::handlePickup(ecs::Entity* _player, ecs::Entity* _pickup, const ecs::EntityManager& _entityManager) {
		_pickup->getComponent<PickupComponent>().pickedUpEntity = _player;
	}

}
