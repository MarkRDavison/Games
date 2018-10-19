#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Sovereign/Services/CollisionResponseService.hpp> 
#include <Sovereign/Core/Definitions.hpp>

namespace sov {
	namespace CollisionResponseServiceTests {

		struct Package {

			Package(void) :
				service() {
				
			}
			
			CollisionResponseService service;

		};

		TEST_CASE("getResolvedMovementFromCollision returns original movement when no collision overlap", "[Sovereign][Services][CollisionResponseService]") {
			Package package{};

			const float OriginalMovement{ 2.0f };
			const float Overlap{ 0.0f };

			REQUIRE(OriginalMovement == package.service.getResolvedMovementFromCollision(Overlap, OriginalMovement));
		}

		TEST_CASE("getResolvedMovementFromCollision returns empty movement when entire movement overlaps exactly", "[Sovereign][Services][CollisionResponseService]") {
			Package package{};

			const float OriginalMovement{ 2.0f };
			const float Overlap{ OriginalMovement };

			REQUIRE(0.0f == package.service.getResolvedMovementFromCollision(Overlap, OriginalMovement));
		}

		TEST_CASE("getResolvedMovementFromCollision returns empty movement when entire movement overlaps exactly and is negative", "[Sovereign][Services][CollisionResponseService]") {
			Package package{};

			const float OriginalMovement{ -2.0f };
			const float Overlap{ 2.0f };

			REQUIRE(0.0f == package.service.getResolvedMovementFromCollision(Overlap, OriginalMovement));
		}

		TEST_CASE("getResolvedMovementFromCollision returns origial movement when offset is greater than movement and is positive", "[Sovereign][Services][CollisionResponseService]") {
			Package package{};

			const float OriginalMovement{ 2.0f };
			const float Overlap{ 4.0f };

			REQUIRE(OriginalMovement == package.service.getResolvedMovementFromCollision(Overlap, OriginalMovement));
		}

		TEST_CASE("getResolvedMovementFromCollision returns origial movement when offset is greater than movement and is negative", "[Sovereign][Services][CollisionResponseService]") {
			Package package{};

			const float OriginalMovement{ -2.0f };
			const float Overlap{ 4.0f };

			REQUIRE(OriginalMovement == package.service.getResolvedMovementFromCollision(Overlap, OriginalMovement));
		}
	}
}
