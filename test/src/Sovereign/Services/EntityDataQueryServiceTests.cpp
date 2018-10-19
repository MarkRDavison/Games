#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Sovereign/Services/EntityDataQueryService.hpp>

namespace sov {
	namespace EntityDataQueryServiceTests {
		
		struct Package {

			Package(void) :
				service(entityData) {
			}

			EntityData entityData;
			EntityDataQueryService service;

		};

		TEST_CASE("doesMoveableEntityExistAtCoordinates returns false if no entities are within the bounds", "[Sovereign][Services][EntityDataQueryService]") {
			Package package{};

			const sf::Vector2f coordinates{ 1.0f, 1.0f };

			REQUIRE_FALSE(package.service.doesMoveableEntityExistAtCoordinates(coordinates.x, coordinates.y));
		}

		TEST_CASE("doesMoveableEntityExistAtCoordinates returns true if the coordinates are within an entity's bounds", "[Sovereign][Services][EntityDataQueryService]") {
			Package package{};

			const sf::Vector2f coordinates{ 1.0f, 1.0f };

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.size = { 1.0f, 1.0f };
			me.position = coordinates;

			REQUIRE(package.service.doesMoveableEntityExistAtCoordinates(coordinates.x, coordinates.y));
		}

		TEST_CASE("getMoveableEntityAtCoordinates throws exception if no entities are within the bounds", "[Sovereign][Services][EntityDataQueryService]") {
			Package package{};

			const sf::Vector2f coordinates{ 1.0f, 1.0f };

			REQUIRE_THROWS_AS(package.service.getMoveableEntityAtCoordinates(coordinates.x, coordinates.y), std::runtime_error);
		}

		TEST_CASE("getMoveableEntityAtCoordinates returns entity if the coordinates are within an entity's bounds", "[Sovereign][Services][EntityDataQueryService]") {
			Package package{};

			const sf::Vector2f coordinates{ 1.0f, 1.0f };

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.size = { 1.0f, 1.0f };
			me.position = coordinates;

			const MoveableEntity& cme = package.service.getMoveableEntityAtCoordinates(coordinates.x, coordinates.y);

			REQUIRE(&me == &cme);
		}

		TEST_CASE("doesEntityExistWithId returns false when entity with given id does not exist", "[Sovereign][Services][EntityDataQueryService]") {
			Package package{};

			REQUIRE_FALSE(package.service.doesEntityExistWithId(1));
		}

		TEST_CASE("doesEntityExistWithId returns true when entity with given id exists", "[Sovereign][Services][EntityDataQueryService]") {
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.id = 1;

			REQUIRE(package.service.doesEntityExistWithId(me.id));
		}

		TEST_CASE("getEntityById throws exception when entity with given id does not exist", "[Sovereign][Services][EntityDataQueryService]") {
			Package package{};

			REQUIRE_THROWS_AS(package.service.getEntityById(1), std::runtime_error);
		}

		TEST_CASE("getEntityById returns entity when entity with given id exists", "[Sovereign][Services][EntityDataQueryService]") {
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.id = 1;

			const MoveableEntity& cme = package.service.getEntityById(me.id);

			REQUIRE(&me == &cme);
		}
	}
}