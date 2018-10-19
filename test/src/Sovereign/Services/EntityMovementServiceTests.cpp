#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Sovereign/Services/EntityMovementService.hpp>
#include <Mocks/Sovereign/Services/CollisionDetectionServiceMock.hpp>
#include <Mocks/Sovereign/Services/CollisionResponseServiceMock.hpp>

namespace sov {
	namespace EntityMovementServiceTests {
		
		struct Package {

			Package(void) :
				service(entityData, collisionDetectionService, collisionResponseService) {
				
			}
			
			EntityData entityData;
			CollisionDetectionServiceMock collisionDetectionService;
			CollisionResponseServiceMock collisionResponseService;
			EntityMovementService service;

		};

		TEST_CASE("updateMoveableEntity does nothing if the entity has no movement value", "[Sovereign][Services][EntityMovementService]") {
			const float delta = 1.0f;
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			
			REQUIRE(sf::Vector2f() == me.movement);
			REQUIRE_NOTHROW(package.service.updateMoveableEntity(me, delta));
			REQUIRE(sf::Vector2f() == me.movement);
		}

		TEST_CASE("updateMoveableEntity requests containing cells for both axis", "[Sovereign][Services][EntityMovementService]") {
			const float delta = 1.0f;
			const float speed = 1.0f;
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.moveRight = true;
			me.speed = speed;

			EntityContainedCell ecc{};

			package.collisionDetectionService.getCellsContainingEntityCallback.registerCallback([&](const MoveableEntity& _entity) -> const EntityContainedCell& { return ecc; });

			package.service.updateMoveableEntity(me, delta);

			REQUIRE(package.collisionDetectionService.getCellsContainingEntityCallback.isInvokedExactly(2));
		}

		TEST_CASE("updateMoveableEntity requests collision response service to get resultant movement if containing cells are valid", "[Sovereign][Services][EntityMovementService]") {
			const float delta = 1.0f;
			const float speed = 1.0f;
			Package package{};

			MoveableEntity& me = package.entityData.moveableEntities.emplace_back();
			me.moveRight = true;
			me.speed = speed;

			EntityContainedCell ecc;
			ecc.valid = true;

			package.collisionDetectionService.getCellsContainingEntityCallback.registerCallback([&](const MoveableEntity& _entity) -> const EntityContainedCell& { return ecc; });
			package.collisionDetectionService.detectTileCollisionOccuredCallback.registerCallback([&](const EntityContainedCell&, sf::FloatRect& _intersection) -> bool {
				_intersection.width = 1.0f;
				_intersection.height = 1.0f;
				return true;
			});
			package.collisionResponseService.getResolvedMovementFromCollisionCallback.registerCallback([&](float, float)->float {return 0.0f; });

			package.service.updateMoveableEntity(me, delta);

			REQUIRE(package.collisionDetectionService.detectTileCollisionOccuredCallback.isInvokedExactly(2));
			REQUIRE(package.collisionResponseService.getResolvedMovementFromCollisionCallback.isInvokedExactly(2));
		}

	}
}
