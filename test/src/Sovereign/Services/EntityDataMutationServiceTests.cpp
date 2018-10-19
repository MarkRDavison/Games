#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Sovereign/Services/EntityDataMutationService.hpp>

namespace sov {
	namespace EntityDataMutationServiceTests {

		struct Package {

			Package(void) :
				service(entityData) {
			}

			EntityData entityData;
			EntityDataMutationService service;

		};

		TEST_CASE("refreshEntities removes all entities that require removal", "[Sovereign][Services][EntityDataMutationService]") {
			Package package{};

			package.entityData.moveableEntities.emplace_back().requiresRemoval = true;
			package.entityData.moveableEntities.emplace_back().requiresRemoval = false;
			package.entityData.moveableEntities.emplace_back().requiresRemoval = true;
			package.entityData.moveableEntities.emplace_back().requiresRemoval = true;

			package.service.refreshEntities();

			REQUIRE(1 == package.entityData.moveableEntities.size());
		}

		TEST_CASE("removeEntity by id marks the entity as requiring removal", "[Sovereign][Services][EntityDataMutationService]") {
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.id = 5;

			package.service.removeEntity(me.id);

			REQUIRE(me.requiresRemoval);
		}

		TEST_CASE("removeEntity by entity marks the entity as requiring removal", "[Sovereign][Services][EntityDataMutationService]") {
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.id = 5;

			package.service.removeEntity(me);

			REQUIRE(me.requiresRemoval);
		}

		TEST_CASE("mineEntity throws exception if the entity does not exist", "[Sovereign][Services][EntityDataMutationService]") {
			Package package{};
			
			REQUIRE_THROWS_AS(package.service.mineEntity(1, 1.0f), std::runtime_error);
		}

		TEST_CASE("mineEntity throws exception if the entity is not mineable", "[Sovereign][Services][EntityDataMutationService]") {
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.id = 5;
			me.isMineable = false;

			REQUIRE_THROWS_AS(package.service.mineEntity(me.id, 1.0f), std::runtime_error);
		}

		TEST_CASE("mineEntity reduces mining time if entity is mineable", "[Sovereign][Services][EntityDataMutationService]") {
			Package package{};

			const float MiningTime = 5.0f;
			const float Delta = 1.0f;

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.id = 5;
			me.isMineable = true;
			me.mineTimeRemaining = MiningTime;

			package.service.mineEntity(me.id, Delta);

			REQUIRE(MiningTime - Delta == me.mineTimeRemaining);
		}

		TEST_CASE("mineEntity returns false if delta is not more than the remining mining time", "[Sovereign][Services][EntityDataMutationService]") {
			Package package{};

			const float MiningTime = 5.0f;
			const float Delta = 1.0f;

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.id = 5;
			me.isMineable = true;
			me.mineTimeRemaining = MiningTime;

			REQUIRE_FALSE(package.service.mineEntity(me.id, Delta));
		}

		TEST_CASE("mineEntity returns true if delta is more than the remining mining time", "[Sovereign][Services][EntityDataMutationService]") {
			Package package{};

			const float MiningTime = 5.0f;
			const float Delta = MiningTime + 1.0f;

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.id = 5;
			me.isMineable = true;
			me.mineTimeRemaining = MiningTime;

			REQUIRE(package.service.mineEntity(me.id, Delta));
		}
	}
}