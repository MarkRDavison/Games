#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Intrusion/Components/TowerTargetComponent.hpp>
#include <Intrusion/Components/TowerTargetingComponent.hpp>
#include <Intrusion/Components/PositionComponent.hpp>
#include <Intrusion/Infrastructure/IntrusionEntityGroups.hpp>
#include <Intrusion/Systems/TowerTargetingSystem.hpp>

namespace itr {
	namespace PathFollowingSystemTests {

		TEST_CASE("Updating system with no towers does nothing", "[Intrusion][System][TowerTargetingSystem]") {
			ecs::EntityManager entityManager;

			TowerTargetingSystem system;

			REQUIRE_NOTHROW(system.update(1.0f, entityManager));
		}

		TEST_CASE("Updating tower entity with a target does nothing", "[Intrusion][System][TowerTargetingSystem]") {
			ecs::EntityManager entityManager;

			TowerTargetingSystem system;

			ecs::Entity& tower = entityManager.addEntity("Tower");
			tower.addGroup(EntityGroup::GTower);
			tower.addComponent<PositionComponent>();
			TowerTargetingComponent& ttc = tower.addComponent<TowerTargetingComponent>();

			ecs::Entity& target1 = entityManager.addEntity("Target1");
			target1.addGroup(EntityGroup::GTowerTarget);
			target1.addComponent<TowerTargetComponent>();
			target1.addComponent<PositionComponent>();

			ecs::Entity& target2 = entityManager.addEntity("Target2");
			target2.addGroup(EntityGroup::GTowerTarget);
			target2.addComponent<TowerTargetComponent>();
			target2.addComponent<PositionComponent>();
			entityManager.refresh();

			ttc.target = entityManager.getWeakEntityRef(&target2);

			system.updateEntity(&tower, 1.0f, entityManager);

			std::shared_ptr<ecs::Entity> t = ttc.target.lock();
			REQUIRE(t);
			REQUIRE(&target2 == t.get());			
		}

		TEST_CASE("Updating tower entity with no target and no available targets does nothing", "[Intrusion][System][TowerTargetingSystem]") {
			ecs::EntityManager entityManager;

			TowerTargetingSystem system;

			ecs::Entity& tower = entityManager.addEntity("Tower");
			tower.addGroup(EntityGroup::GTower);
			tower.addComponent<PositionComponent>();
			TowerTargetingComponent& ttc = tower.addComponent<TowerTargetingComponent>();
			entityManager.refresh();
			
			system.updateEntity(&tower, 1.0f, entityManager);

			REQUIRE(ttc.target.expired());
		}

		TEST_CASE("Updating tower entity with no target and one available target out of range does nothing", "[Intrusion][System][TowerTargetingSystem]") {
			const sf::Vector2f TowerPosition{ 1.0f, 1.0f };
			const sf::Vector2f TargetPosition{ 5.0f, 5.0f };
			const float TowerRange{ 2.0f };
			ecs::EntityManager entityManager;

			TowerTargetingSystem system;

			ecs::Entity& tower = entityManager.addEntity("Tower");
			tower.addGroup(EntityGroup::GTower);
			tower.addComponent<PositionComponent>(TowerPosition);
			TowerTargetingComponent& ttc = tower.addComponent<TowerTargetingComponent>();
			ttc.range = TowerRange;

			ecs::Entity& target1 = entityManager.addEntity("Target1");
			target1.addGroup(EntityGroup::GTowerTarget);
			target1.addComponent<TowerTargetComponent>();
			target1.addComponent<PositionComponent>(TargetPosition);

			entityManager.refresh();
			system.updateEntity(&tower, 1.0f, entityManager);

			REQUIRE(ttc.target.expired());
		}

		TEST_CASE("Updating tower entity with no target and one available target in range sets the target", "[Intrusion][System][TowerTargetingSystem]") {
			const sf::Vector2f TowerPosition{ 1.0f, 1.0f };
			const sf::Vector2f TargetPosition{ 2.0f, 2.0f };
			const float TowerRange{ 2.0f };
			ecs::EntityManager entityManager;

			TowerTargetingSystem system;

			ecs::Entity& tower = entityManager.addEntity("Tower");
			tower.addGroup(EntityGroup::GTower);
			tower.addComponent<PositionComponent>(TowerPosition);
			TowerTargetingComponent& ttc = tower.addComponent<TowerTargetingComponent>();
			ttc.range = TowerRange;

			ecs::Entity& target1 = entityManager.addEntity("Target1");
			target1.addGroup(EntityGroup::GTowerTarget);
			target1.addComponent<TowerTargetComponent>();
			target1.addComponent<PositionComponent>(TargetPosition);
			entityManager.refresh();

			system.updateEntity(&tower, 1.0f, entityManager);

			std::shared_ptr<ecs::Entity> t = ttc.target.lock();
			REQUIRE(t);
			REQUIRE(&target1 == t.get());
		}

		TEST_CASE("Updating tower entity with no target and multiple available targets in range sets the target as the closest target", "[Intrusion][System][TowerTargetingSystem]") {
			const sf::Vector2f TowerPosition{ 1.0f, 1.0f };
			const sf::Vector2f TargetPosition{ 2.0f, 2.0f };
			const float TowerRange{ 20.0f };
			ecs::EntityManager entityManager;

			TowerTargetingSystem system;

			ecs::Entity& tower = entityManager.addEntity("Tower");
			tower.addGroup(EntityGroup::GTower);
			tower.addComponent<PositionComponent>(TowerPosition);
			TowerTargetingComponent& ttc = tower.addComponent<TowerTargetingComponent>();
			ttc.range = TowerRange;

			ecs::Entity& target1 = entityManager.addEntity("Target1");
			target1.addGroup(EntityGroup::GTowerTarget);
			target1.addComponent<TowerTargetComponent>();
			target1.addComponent<PositionComponent>(TargetPosition + sf::Vector2f(2.0f, 0.0f));

			ecs::Entity& target2 = entityManager.addEntity("Target2");
			target2.addGroup(EntityGroup::GTowerTarget);
			target2.addComponent<TowerTargetComponent>();
			target2.addComponent<PositionComponent>(TargetPosition + sf::Vector2f(1.0f, 0.0f));

			ecs::Entity& target3 = entityManager.addEntity("Target3");
			target3.addGroup(EntityGroup::GTowerTarget);
			target3.addComponent<TowerTargetComponent>();
			target3.addComponent<PositionComponent>(TargetPosition + sf::Vector2f(0.0f, 0.0f));
			entityManager.refresh();

			system.updateEntity(&tower, 1.0f, entityManager);

			std::shared_ptr<ecs::Entity> t = ttc.target.lock();
			REQUIRE(t);
			REQUIRE(&target3 == t.get());
		}

		TEST_CASE("targetStillInRange returns true when target still in range of tower", "[Intrusion][System][TowerTargetingSystem]") {
			const sf::Vector2f TowerPosition{ 1.0f, 1.0f };
			const sf::Vector2f TargetPosition{ 2.0f, 2.0f };
			const float TowerRange{ 2.0f };
			ecs::EntityManager entityManager;

			TowerTargetingSystem system;

			ecs::Entity& target1 = entityManager.addEntity("Target1");
			target1.addGroup(EntityGroup::GTowerTarget);
			target1.addComponent<TowerTargetComponent>();
			target1.addComponent<PositionComponent>(TargetPosition);

			ecs::Entity& tower = entityManager.addEntity("Tower");
			tower.addGroup(EntityGroup::GTower);
			PositionComponent& pc = tower.addComponent<PositionComponent>(TowerPosition);
			TowerTargetingComponent& ttc = tower.addComponent<TowerTargetingComponent>();
			ttc.range = TowerRange;
			entityManager.refresh();
			ttc.target = entityManager.getWeakEntityRef(&target1);

			REQUIRE(TowerTargetingSystem::targetStillInRange(pc, ttc));
		}

		TEST_CASE("targetStillInRange returns false when target out of range of tower", "[Intrusion][System][TowerTargetingSystem]") {
			const sf::Vector2f TowerPosition{ 1.0f, 1.0f };
			const sf::Vector2f TargetPosition{ 20.0f, 20.0f };
			const float TowerRange{ 2.0f };
			ecs::EntityManager entityManager;

			TowerTargetingSystem system;

			ecs::Entity& target1 = entityManager.addEntity("Target1");
			target1.addGroup(EntityGroup::GTowerTarget);
			target1.addComponent<TowerTargetComponent>();
			target1.addComponent<PositionComponent>(TargetPosition);

			ecs::Entity& tower = entityManager.addEntity("Tower");
			tower.addGroup(EntityGroup::GTower);
			PositionComponent& pc = tower.addComponent<PositionComponent>(TowerPosition);
			TowerTargetingComponent& ttc = tower.addComponent<TowerTargetingComponent>();
			ttc.range = TowerRange;
			entityManager.refresh();
			ttc.target = entityManager.getWeakEntityRef(&target1);

			REQUIRE_FALSE(TowerTargetingSystem::targetStillInRange(pc, ttc));
		}

		TEST_CASE("updating a tower whose target is now out of range removes its target and tries to find another", "[Intrusion][System][TowerTargetingSystem]") {
			const sf::Vector2f TowerPosition{ 1.0f, 1.0f };
			const sf::Vector2f TargetPosition{ 2.0f, 2.0f };
			const float TowerRange{ 2.0f };
			ecs::EntityManager entityManager;

			TowerTargetingSystem system;

			ecs::Entity& tower = entityManager.addEntity("Tower");
			tower.addGroup(EntityGroup::GTower);
			tower.addComponent<PositionComponent>(TowerPosition);
			TowerTargetingComponent& ttc = tower.addComponent<TowerTargetingComponent>();
			ttc.range = TowerRange;

			ecs::Entity& target1 = entityManager.addEntity("Target1");
			target1.addGroup(EntityGroup::GTowerTarget);
			target1.addComponent<TowerTargetComponent>();
			target1.addComponent<PositionComponent>(TargetPosition + sf::Vector2f(20.0f, 0.0f));

			ecs::Entity& target2 = entityManager.addEntity("Target2");
			target2.addGroup(EntityGroup::GTowerTarget);
			target2.addComponent<TowerTargetComponent>();
			target2.addComponent<PositionComponent>(TargetPosition + sf::Vector2f(0.0f, 0.0f));

			entityManager.refresh();

			ttc.target = entityManager.getWeakEntityRef(&target1);

			system.updateEntity(&tower, 1.0f, entityManager);

			std::shared_ptr<ecs::Entity> t = ttc.target.lock();
			REQUIRE(t);
			REQUIRE(&target2 == t.get());
		}

	}
}
