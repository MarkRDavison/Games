#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Intrusion/Infrastructure/IntrusionEntityGroups.hpp>
#include <Intrusion/Systems/TowerFiringSystem.hpp>
#include <Intrusion/Components/TowerTargetingComponent.hpp>
#include <Intrusion/Components/TowerFiringComponent.hpp>

namespace itr {
	namespace TowerFiringSystemTests {

		TEST_CASE("updating entity with no target does nothing", "[Intrusion][System][TowerFiringSystem]") {
			ecs::EntityManager entityManager;

			ecs::Entity& tower = entityManager.addEntity("Tower");
			tower.addGroup(EntityGroup::GTower);
			TowerTargetingComponent& ttc = tower.addComponent<TowerTargetingComponent>();
			TowerFiringComponent& tfc = tower.addComponent<TowerFiringComponent>();

			TowerFiringSystem system;

			REQUIRE_NOTHROW(system.updateEntity(&tower, 1.0f, entityManager));
		}

		TEST_CASE("updating tower increases the cooldown", "[Intrusion][System][TowerFiringSystem]") {
			ecs::EntityManager entityManager;

			ecs::Entity& tower = entityManager.addEntity("Tower");
			tower.addGroup(EntityGroup::GTower);
			TowerTargetingComponent& ttc = tower.addComponent<TowerTargetingComponent>();
			TowerFiringComponent& tfc = tower.addComponent<TowerFiringComponent>();
			tfc.firingCooldown = 2.0f;

			TowerFiringSystem system;

			system.updateEntity(&tower, 1.0f, entityManager);

			REQUIRE(1.0f == tfc.accumulatedFiringCooldown);
		}

		TEST_CASE("updating tower does not increase the cooldown past the maximum", "[Intrusion][System][TowerFiringSystem]") {
			ecs::EntityManager entityManager;

			ecs::Entity& tower = entityManager.addEntity("Tower");
			tower.addGroup(EntityGroup::GTower);
			TowerTargetingComponent& ttc = tower.addComponent<TowerTargetingComponent>();
			TowerFiringComponent& tfc = tower.addComponent<TowerFiringComponent>();
			tfc.firingCooldown = 2.0f;

			TowerFiringSystem system;

			system.updateEntity(&tower, 10.0f, entityManager);

			REQUIRE(tfc.firingCooldown == tfc.accumulatedFiringCooldown);
		}

		TEST_CASE("updating tower that has cooled down but has no target does nothing", "[Intrusion][System][TowerFiringSystem]") {
			ecs::EntityManager entityManager;

			ecs::Entity& tower = entityManager.addEntity("Tower");
			tower.addGroup(EntityGroup::GTower);
			TowerTargetingComponent& ttc = tower.addComponent<TowerTargetingComponent>();
			TowerFiringComponent& tfc = tower.addComponent<TowerFiringComponent>();
			tfc.firingCooldown = 2.0f;
			tfc.accumulatedFiringCooldown = 2.0f;

			TowerFiringSystem system;

			system.updateEntity(&tower, 10.0f, entityManager);

			REQUIRE(tfc.firingCooldown == tfc.accumulatedFiringCooldown);
		}

		TEST_CASE("updating tower that has cooled down and has a target spawns a projectile", "[Intrusion][System][TowerFiringSystem]") {
			ecs::EntityManager entityManager;

			ecs::Entity& tower = entityManager.addEntity("Tower");
			tower.addGroup(EntityGroup::GTower);
			TowerTargetingComponent& ttc = tower.addComponent<TowerTargetingComponent>();
			TowerFiringComponent& tfc = tower.addComponent<TowerFiringComponent>();
			tfc.firingCooldown = 2.0f;
			tfc.accumulatedFiringCooldown = 2.0f;
			tfc.projectilePrototype.prototypeName = "PrototypeName";

			ecs::Entity& target = entityManager.addEntity("Target");
			entityManager.refresh();
			ttc.target = entityManager.getWeakEntityRef(&target);

			bool projectileSpawned = false;
			TowerFiringSystem system;
			system.projectileSpawned = [&](const ParsedProjectile& _projectilePrototype, ecs::Entity *_source, ecs::Entity *_target) {
				REQUIRE(&tower == _source);
				REQUIRE(&target == _target);
				REQUIRE(tfc.projectilePrototype.prototypeName == _projectilePrototype.prototypeName);
				projectileSpawned = true;
			};

			system.updateEntity(&tower, 10.0f, entityManager);

			REQUIRE(projectileSpawned);
		}

		TEST_CASE("updating tower that has cooled down and has a target resets the accumulated cooldown", "[Intrusion][System][TowerFiringSystem]") {
			ecs::EntityManager entityManager;

			ecs::Entity& tower = entityManager.addEntity("Tower");
			tower.addGroup(EntityGroup::GTower);
			TowerTargetingComponent& ttc = tower.addComponent<TowerTargetingComponent>();
			TowerFiringComponent& tfc = tower.addComponent<TowerFiringComponent>();
			tfc.firingCooldown = 2.0f;
			tfc.accumulatedFiringCooldown = 2.0f;
			tfc.projectilePrototype.prototypeName = "PrototypeName";

			ecs::Entity& target = entityManager.addEntity("Target"); 
			entityManager.refresh();
			ttc.target = entityManager.getWeakEntityRef(&target);

			TowerFiringSystem system;

			system.updateEntity(&tower, 10.0f, entityManager);

			REQUIRE(0.0f == tfc.accumulatedFiringCooldown);
		}
	}
}
