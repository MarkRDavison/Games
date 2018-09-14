#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Intrusion/Services/TowerPlaceableSurfaceService.hpp>
#include <Mocks/Intrusion/Infrastructure/TowerPlaceableSurfaceMock.hpp>

namespace itr {
	namespace TowerPlaceableSurfaceServiceTests {

		TEST_CASE("New service's active surface is nullptr", "[Intrusion][Service][TowerPlaceableSurfaceService]") {
			TowerPlaceableSurfaceService service;

			REQUIRE(nullptr == service.getActiveSurface());
		}

		TEST_CASE("Setting service's active surface does as expected", "[Intrusion][Service][TowerPlaceableSurfaceService]") {
			TowerPlaceableSurfaceService service;
			TowerPlaceableSurfaceMock surface;

			service.setActiveSurface(&surface);

			REQUIRE(&surface == service.getActiveSurface());
		}
	}
}
