#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Kingdom/Systems/WaypointSystem.hpp>
#include <Kingdom/Components/PositionComponent.hpp>
#include <Kingdom/Components/MovementComponent.hpp>
#include <Kingdom/Components/WaypointComponent.hpp>

namespace kdm {
	namespace WaypointSystemTests {

		TEST_CASE("Updating entity with no waypoints in the component does nothing", "[Kingdom][System][WaypointSystem]") {
			const sf::Vector2f startPosition{ 1.0f, 1.0f };

			ecs::EntityManager em;
			ecs::Entity& e = em.addEntity();
			e.addComponent<PositionComponent>(startPosition);
			e.addComponent<MovementComponent>().speed = 1.0f;
			e.addComponent<WaypointComponent>().waypoints = {};

			kdm::WaypointSytem system;

			system.updateEntity(&e, 1.0f);

			REQUIRE(0 == e.getComponent<WaypointComponent>().currentWaypointIndex);
		}

		TEST_CASE("Updating entity with one waypoint sets target towards that waypoint", "[Kingdom][System][WaypointSystem]") {
			const sf::Vector2f startPosition{ 1.0f, 1.0f };

			ecs::EntityManager em;
			ecs::Entity& e = em.addEntity();
			e.addComponent<PositionComponent>(startPosition);
			e.addComponent<MovementComponent>().speed = 1.0f;
			e.addComponent<WaypointComponent>().waypoints = {{2.0f, 1.0f}};

			kdm::WaypointSytem system;

			system.updateEntity(&e, 1.0f);

			REQUIRE(0 == e.getComponent<WaypointComponent>().currentWaypointIndex);
			REQUIRE(e.getComponent<WaypointComponent>().waypoints[0] == e.getComponent<MovementComponent>().target);
			REQUIRE(e.getComponent<MovementComponent>().targetMode);
		}

		TEST_CASE("Updating entity with one waypoint set at same position updates current waypoint index", "[Kingdom][System][WaypointSystem]") {
			const sf::Vector2f startPosition{ 1.0f, 1.0f };

			ecs::EntityManager em;
			ecs::Entity& e = em.addEntity();
			e.addComponent<PositionComponent>(startPosition);
			e.addComponent<MovementComponent>().speed = 1.0f;
			e.addComponent<WaypointComponent>().waypoints = { startPosition };

			kdm::WaypointSytem system;

			system.updateEntity(&e, 1.0f);

			REQUIRE(1 == e.getComponent<WaypointComponent>().currentWaypointIndex);
			REQUIRE(sf::Vector2f() == e.getComponent<MovementComponent>().velocity);
			REQUIRE(sf::Vector2f() == e.getComponent<MovementComponent>().target);
			REQUIRE_FALSE(e.getComponent<MovementComponent>().targetMode);
		}

		TEST_CASE("Updating entity that cant reach a waypoint in one update sets target to it", "[Kingdom][System][WaypointSystem]") {
			const sf::Vector2f startPosition{ 1.0f, 1.0f };

			ecs::EntityManager em;
			ecs::Entity& e = em.addEntity();
			e.addComponent<PositionComponent>(startPosition);
			e.addComponent<MovementComponent>().speed = 1.0f;
			e.addComponent<WaypointComponent>().waypoints = { {3.0f, 1.0f} };

			kdm::WaypointSytem system;

			system.updateEntity(&e, 1.0f);
			
			REQUIRE(0 == e.getComponent<WaypointComponent>().currentWaypointIndex);
			REQUIRE(e.getComponent<WaypointComponent>().waypoints[0] == e.getComponent<MovementComponent>().target);
			REQUIRE(e.getComponent<MovementComponent>().targetMode);
		}
	}
}
