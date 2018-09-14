#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Intrusion/Systems/PathFollowingSystem.hpp>
#include <Intrusion/Components/PositionComponent.hpp>
#include <Intrusion/Components/PathFollowComponent.hpp>
#include <Mocks/Intrusion/Services/LevelResourceServiceMock.hpp>

namespace itr {
	namespace PathFollowingSystemTests {

		TEST_CASE("Updating entity with no path to follow does nothing", "[Intrusion][System][PathFollowingSystem]") {
			ecs::EntityManager em;
			ecs::Entity& e = em.addEntity();
			e.addComponent<PositionComponent>();
			e.addComponent<PathFollowComponent>();

			LevelResourceServiceMock levelResourceServiceMock{};
			PathFollowingSystem system(levelResourceServiceMock);

			REQUIRE_NOTHROW(system.updateEntity(1.0f, &e, em));
		}

		TEST_CASE("Updating entity already at the end of the path clears the path", "[Intrusion][System][PathFollowingSystem]") {
			const sf::Vector2f end{ 5.0f, 5.0f };

			ecs::EntityManager em;
			ecs::Entity& e = em.addEntity();
			e.addComponent<PositionComponent>(end);
			PathFollowComponent& pfc = e.addComponent<PathFollowComponent>();
			pfc.speed = 1.0f;
			pfc.pathPoints.push(end);

			LevelResourceServiceMock levelResourceServiceMock{};
			PathFollowingSystem system(levelResourceServiceMock);

			REQUIRE_NOTHROW(system.updateEntity(1.0f, &e, em));

			REQUIRE(pfc.pathPoints.empty());
		}

		TEST_CASE("Updating entity that can reach the first node on its path pops the first node and moves it to the node", "[Intrusion][System][PathFollowingSystem]") {
			const sf::Vector2f start{ 5.0f, 5.0f };

			ecs::EntityManager em;
			ecs::Entity& e = em.addEntity();
			PositionComponent& pc = e.addComponent<PositionComponent>(start);
			PathFollowComponent& pfc = e.addComponent<PathFollowComponent>();
			pfc.speed = 1.0f;
			pfc.pathPoints.push(start + sf::Vector2f(1.0f, 0.0f));
			pfc.pathPoints.push(start + sf::Vector2f(2.0f, 0.0f));

			LevelResourceServiceMock levelResourceServiceMock{};
			PathFollowingSystem system(levelResourceServiceMock);

			REQUIRE_NOTHROW(system.updateEntity(1.0f, &e, em));

			REQUIRE(pfc.pathPoints.size() == 1);
			REQUIRE(start + sf::Vector2f(1.0f, 0.0f) == pc.position);
		}

		TEST_CASE("Updating entity that cannot reach the the target node does not pop the node and moves it as far as it can", "[Intrusion][System][PathFollowingSystem]") {
			const sf::Vector2f start{ 5.0f, 5.0f };
			const float delta = 1.0f;

			ecs::EntityManager em;
			ecs::Entity& e = em.addEntity();
			PositionComponent& pc = e.addComponent<PositionComponent>(start);
			PathFollowComponent& pfc = e.addComponent<PathFollowComponent>();
			pfc.speed = 1.0f;
			pfc.pathPoints.push(start + sf::Vector2f(pfc.speed * delta * 2.0f, 0.0f));

			LevelResourceServiceMock levelResourceServiceMock{};
			PathFollowingSystem system(levelResourceServiceMock);

			REQUIRE_NOTHROW(system.updateEntity(1.0f, &e, em));

			REQUIRE(pfc.pathPoints.size() == 1);
			REQUIRE(start + sf::Vector2f(pfc.speed * delta, 0.0f) == pc.position);
		}

		TEST_CASE("Updating entity that can reach past its first node but not to its second node gets move to between the first and second", "[Intrusion][System][PathFollowingSystem]") {
			const sf::Vector2f start{ 5.0f, 5.0f };
			const float delta = 1.0f;

			ecs::EntityManager em;
			ecs::Entity& e = em.addEntity();
			PositionComponent& pc = e.addComponent<PositionComponent>(start);
			PathFollowComponent& pfc = e.addComponent<PathFollowComponent>();
			pfc.speed = 1.5f;
			pfc.pathPoints.push(start + sf::Vector2f(1.0f, 0.0f));
			pfc.pathPoints.push(start + sf::Vector2f(2.0f, 0.0f));

			LevelResourceServiceMock levelResourceServiceMock{};
			PathFollowingSystem system(levelResourceServiceMock);

			REQUIRE_NOTHROW(system.updateEntity(1.0f, &e, em));

			REQUIRE(pfc.pathPoints.size() == 1);
			REQUIRE(start + sf::Vector2f(pfc.speed * delta, 0.0f) == pc.position);
		}

		TEST_CASE("Updating entity that can reach past its first node but not to its second node gets move to between the first and second even if they aren't in the same direction", "[Intrusion][System][PathFollowingSystem]") {
			const sf::Vector2f start{ 5.0f, 5.0f };
			const float delta = 1.0f;

			ecs::EntityManager em;
			ecs::Entity& e = em.addEntity();
			PositionComponent& pc = e.addComponent<PositionComponent>(start);
			PathFollowComponent& pfc = e.addComponent<PathFollowComponent>();
			pfc.speed = 1.5f;
			pfc.pathPoints.push(start + sf::Vector2f(1.0f, 0.0f));
			pfc.pathPoints.push(start + sf::Vector2f(1.0f, 1.0f));

			LevelResourceServiceMock levelResourceServiceMock{};
			PathFollowingSystem system(levelResourceServiceMock);

			REQUIRE_NOTHROW(system.updateEntity(1.0f, &e, em));

			REQUIRE(pfc.pathPoints.size() == 1);
			REQUIRE(start + sf::Vector2f(1.0f, 0.5f) == pc.position);
		}

		TEST_CASE("An entity reaching the end notifies the level resource service", "[Intrusion][System][PathFollowingSystem]") {
			const sf::Vector2f end{ 5.0f, 5.0f };

			ecs::EntityManager em;
			ecs::Entity& e = em.addEntity();
			e.addComponent<PositionComponent>(end);
			PathFollowComponent& pfc = e.addComponent<PathFollowComponent>();
			pfc.speed = 1.0f;
			pfc.pathPoints.push(end);

			bool updateResourceInvoked{ false };
			LevelResourceServiceMock levelResourceServiceMock{};
			levelResourceServiceMock.updateResourceCallback = [&](const std::string& _resourceName, int _amount) {
				updateResourceInvoked = true;
			};
			PathFollowingSystem system(levelResourceServiceMock);
			
			REQUIRE_NOTHROW(system.updateEntity(1.0f, &e, em));
			REQUIRE(updateResourceInvoked);
		}
	}
}