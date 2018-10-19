#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Sovereign/Services/PlayerControlService.hpp>
#include <Mocks/Infrastructure/InputManagerMock.hpp>

namespace sov {
	namespace PlayerControlServiceTests {

		struct Package {
			
			Package(void) :
				service(entityData, controlBindings) {
				
			}

			EntityData entityData;
			ControlBindings controlBindings;
			PlayerControlService service;
		};

		TEST_CASE("handleKeyEvent for key pressed event updates the player entity's move left if the control bindings match", "[Sovereign][Services][PlayerControlService]") {
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.isPlayer = true;

			sf::Event event{};
			event.type = sf::Event::KeyPressed;
			event.key.code = package.controlBindings.moveLeftBinding;

			REQUIRE(package.service.handleKeyEvent(event));
			REQUIRE(me.moveLeft);
		}

		TEST_CASE("handleKeyEvent for key released event updates the player entity's move left if the control bindings match", "[Sovereign][Services][PlayerControlService]") {
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.isPlayer = true;
			me.moveLeft = true;

			sf::Event event{};
			event.type = sf::Event::KeyReleased;
			event.key.code = package.controlBindings.moveLeftBinding;

			REQUIRE(package.service.handleKeyEvent(event));
			REQUIRE_FALSE(me.moveLeft);
		}

		TEST_CASE("handleKeyEvent for key pressed event updates the player entity's move right if the control bindings match", "[Sovereign][Services][PlayerControlService]") {
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.isPlayer = true;

			sf::Event event{};
			event.type = sf::Event::KeyPressed;
			event.key.code = package.controlBindings.moveRightBinding;

			REQUIRE(package.service.handleKeyEvent(event));
			REQUIRE(me.moveRight);
		}

		TEST_CASE("handleKeyEvent for key released event updates the player entity's move right if the control bindings match", "[Sovereign][Services][PlayerControlService]") {
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.isPlayer = true;
			me.moveLeft = true;

			sf::Event event{};
			event.type = sf::Event::KeyReleased;
			event.key.code = package.controlBindings.moveRightBinding;

			REQUIRE(package.service.handleKeyEvent(event));
			REQUIRE_FALSE(me.moveRight);
		}

		TEST_CASE("handleKeyEvent for key pressed event updates the player entity's move up if the control bindings match", "[Sovereign][Services][PlayerControlService]") {
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.isPlayer = true;

			sf::Event event{};
			event.type = sf::Event::KeyPressed;
			event.key.code = package.controlBindings.moveUpBinding;

			REQUIRE(package.service.handleKeyEvent(event));
			REQUIRE(me.moveUp);
		}

		TEST_CASE("handleKeyEvent for key released event updates the player entity's move up if the control bindings match", "[Sovereign][Services][PlayerControlService]") {
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.isPlayer = true;
			me.moveLeft = true;

			sf::Event event{};
			event.type = sf::Event::KeyReleased;
			event.key.code = package.controlBindings.moveUpBinding;

			REQUIRE(package.service.handleKeyEvent(event));
			REQUIRE_FALSE(me.moveUp);
		}

		TEST_CASE("handleKeyEvent for key pressed event updates the player entity's move down if the control bindings match", "[Sovereign][Services][PlayerControlService]") {
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.isPlayer = true;

			sf::Event event{};
			event.type = sf::Event::KeyPressed;
			event.key.code = package.controlBindings.moveDownBinding;

			REQUIRE(package.service.handleKeyEvent(event));
			REQUIRE(me.moveDown);
		}

		TEST_CASE("handleKeyEvent for key released event updates the player entity's move down if the control bindings match", "[Sovereign][Services][PlayerControlService]") {
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.isPlayer = true;
			me.moveLeft = true;

			sf::Event event{};
			event.type = sf::Event::KeyReleased;
			event.key.code = package.controlBindings.moveDownBinding;

			REQUIRE(package.service.handleKeyEvent(event));
			REQUIRE_FALSE(me.moveDown);
		}

	}
}
