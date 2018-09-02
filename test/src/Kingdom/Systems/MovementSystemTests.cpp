#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Kingdom/Systems/MovementSystem.hpp>
#include <Kingdom/Components/PositionComponent.hpp>
#include <Kingdom/Components/MovementComponent.hpp>

namespace kdm {
	namespace WaypointSystemTests {

		TEST_CASE("Updating an entity moves it as far as its velocity indicates if not in target mode", "[Kingdom][System][MovementSystem]") {
			const sf::Vector2f startPosition{ 1.0f, 1.0f };

			ecs::EntityManager em;
			ecs::Entity& e = em.addEntity();
			e.addComponent<PositionComponent>(startPosition);
			auto& mc = e.addComponent<MovementComponent>();

			mc.speed = 1.0f;
			mc.velocity = { 1.0f, 1.0f };
			mc.targetMode = false;

			MovementSystem ms;

			ms.updateEntity(&e, 1.0f);

			REQUIRE(startPosition + mc.velocity == e.getComponent<PositionComponent>().position);
		}

		TEST_CASE("Updating an entity that can reach its target moves it to its target in target mode", "[Kingdom][System][MovementSystem]") {
			const sf::Vector2f startPosition{ 1.0f, 1.0f };

			ecs::EntityManager em;
			ecs::Entity& e = em.addEntity();
			e.addComponent<PositionComponent>(startPosition);
			auto& mc = e.addComponent<MovementComponent>();

			mc.speed = 1.0f;
			mc.velocity = {};
			mc.targetMode = true;
			mc.target = { startPosition + sf::Vector2f(mc.speed, 0.0f) };

			MovementSystem ms;

			ms.updateEntity(&e, 1.0f);

			REQUIRE(startPosition + sf::Vector2f(mc.speed, 0.0f) == e.getComponent<PositionComponent>().position);
			REQUIRE(sf::Vector2f() == e.getComponent<MovementComponent>().target);
			REQUIRE_FALSE(e.getComponent<MovementComponent>().targetMode);
		}

		TEST_CASE("Updating an entity that cant reach its target moves it towards it if in target mode", "[Kingdom][System][MovementSystem]") {
			const sf::Vector2f startPosition{ 1.0f, 1.0f };

			ecs::EntityManager em;
			ecs::Entity& e = em.addEntity();
			e.addComponent<PositionComponent>(startPosition);
			auto& mc = e.addComponent<MovementComponent>();

			mc.speed = 1.0f;
			mc.velocity = {};
			mc.targetMode = true;
			mc.target = { startPosition + sf::Vector2f(mc.speed * 2.0f, 0.0f) };

			const sf::Vector2f target(mc.target);

			MovementSystem ms;

			ms.updateEntity(&e, 1.0f);

			REQUIRE(startPosition + sf::Vector2f(mc.speed, 0.0f) == e.getComponent<PositionComponent>().position);

			ms.updateEntity(&e, 1.0f);
			REQUIRE(target == e.getComponent<PositionComponent>().position);
		}
	}
}