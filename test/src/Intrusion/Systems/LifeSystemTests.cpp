#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Intrusion/Infrastructure/IntrusionEntityGroups.hpp>
#include <Intrusion/Systems/LifeSystem.hpp>
#include <Intrusion/Components/LifeComponent.hpp>
#include <Mocks/Intrusion/Services/LevelResourceServiceMock.hpp>
#include <Intrusion/Infrastructure/IntrusionDefinitions.hpp>

namespace itr {
	namespace TowerFiringSystemTests {

		TEST_CASE("Updating entity with health does nothing", "[Intrusion][System][LifeSystem]") {
			ecs::EntityManager entityManager;

			ecs::Entity& e = entityManager.addEntity("LifeEntity");
			e.addGroup(EntityGroup::GLife);
			LifeComponent& lc = e.addComponent<LifeComponent>();
			lc.health = 10.0f;

			LevelResourceServiceMock resourceService;
			LifeSystem system(resourceService);

			REQUIRE_NOTHROW(system.updateEntity(&e, 1.0f, entityManager));
		}

		TEST_CASE("Updating an entity with no health destroys it", "[Intrusion][System][LifeSystem]") {
			ecs::EntityManager entityManager;

			ecs::Entity& e = entityManager.addEntity("LifeEntity");
			e.addGroup(EntityGroup::GLife);
			LifeComponent& lc = e.addComponent<LifeComponent>();
			lc.health = 0.0f;

			LevelResourceServiceMock resourceService;
			LifeSystem system(resourceService);

			system.updateEntity(&e, 1.0f, entityManager);

			REQUIRE_FALSE(e.isAlive());
		}

		TEST_CASE("destroying an entity updates the kill resource", "[Intrusion][System][LifeSystem]") {
			ecs::EntityManager entityManager;

			ecs::Entity& e = entityManager.addEntity("LifeEntity");
			e.addGroup(EntityGroup::GLife);
			LifeComponent& lc = e.addComponent<LifeComponent>();
			lc.health = 0.0f;

			bool killResourceUpdated = false;
			LevelResourceServiceMock resourceService;
			resourceService.updateResourceCallback = [&](const std::string& _resourceName, int _amount) {
				REQUIRE(Definitions::KillsResourceName == _resourceName);
				REQUIRE(1 == _amount);
				killResourceUpdated = true;
			};
			LifeSystem system(resourceService);

			system.updateEntity(&e, 1.0f, entityManager);

			REQUIRE(killResourceUpdated);
		}

		TEST_CASE("Updating an entity with health and life adjustments clears the queue", "[Intrusion][System][LifeSystem]") {
			const float StartingHealth = 10.0f;
			ecs::EntityManager entityManager;

			ecs::Entity& e = entityManager.addEntity("LifeEntity");
			e.addGroup(EntityGroup::GLife);
			LifeComponent& lc = e.addComponent<LifeComponent>();
			lc.health = StartingHealth;
			lc.lifeAdjustments.push({});

			LevelResourceServiceMock resourceService;
			LifeSystem system(resourceService);

			system.updateEntity(&e, 1.0f, entityManager);

			REQUIRE(lc.lifeAdjustments.empty());
		}

		TEST_CASE("Updating an entity with health and life adjustments applies the adjustments", "[Intrusion][System][LifeSystem]") {
			const float StartingHealth = 10.0f;
			const float HealthChange = -5.0f;
			const float StartingArmour = 20.0f;
			const float ArmourChange = -15.0f;
			const float StartingShields = 100.0f;
			const float ShieldChange = -50.0f;
			ecs::EntityManager entityManager;

			ecs::Entity& e = entityManager.addEntity("LifeEntity");
			e.addGroup(EntityGroup::GLife);
			LifeComponent& lc = e.addComponent<LifeComponent>();
			lc.health = StartingHealth;
			lc.armour = StartingArmour;
			lc.shields = StartingShields;
			{
				LifeBundle bundle{};
				bundle.health = HealthChange;
				bundle.armour = ArmourChange;
				bundle.shields = ShieldChange;
				lc.lifeAdjustments.push(bundle);
			}

			LevelResourceServiceMock resourceService;
			LifeSystem system(resourceService);

			system.updateEntity(&e, 1.0f, entityManager);

			REQUIRE(StartingHealth + HealthChange == lc.health);
			REQUIRE(StartingArmour + ArmourChange == lc.armour);
			REQUIRE(StartingShields + ShieldChange == lc.shields);
		}

		TEST_CASE("On destroying an entity any resource it spawns on death are applied", "[Intrusion][System][LifeSystem]") {
			const int GoldAmount = 50;
			ecs::EntityManager entityManager;

			ecs::Entity& e = entityManager.addEntity("LifeEntity");
			e.addGroup(EntityGroup::GLife);
			LifeComponent& lc = e.addComponent<LifeComponent>();
			lc.health = 0.0f;
			{
				ResourceBundle::Resource resource{};
				resource.name = Definitions::GoldResourceName;
				resource.amount = GoldAmount;
				lc.onDeathResources.resources.push_back(resource);
			}

			bool deathResourcesUpdated = false;
			LevelResourceServiceMock resourceService;
			resourceService.receiveResourceBundleCallback = [&](const ResourceBundle& _resourceBundle) {
				REQUIRE(1 == _resourceBundle.resources.size());
				REQUIRE(Definitions::GoldResourceName == _resourceBundle.resources[0].name);
				REQUIRE(GoldAmount == _resourceBundle.resources[0].amount);
				deathResourcesUpdated = true;
			};
			LifeSystem system(resourceService);

			system.updateEntity(&e, 1.0f, entityManager);

			REQUIRE(deathResourcesUpdated);
		}

	}
}
