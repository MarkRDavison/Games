#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Kingdom/Services/SurfaceService.hpp>
#include <Kingdom/Exceptions/SurfaceNotFoundException.hpp>
#include <Mocks/Kingdom/Services/PathSurfaceMock.hpp>

namespace kdm {
	namespace SurfaceServiceTests {
		TEST_CASE("Trying to get the current surface when it is not set throws a surface not set exception", "[Services][SurfaceService]") {
			SurfaceService service;

			REQUIRE_THROWS_AS(service.getCurrentSurface(), SurfaceNotFoundException);
		}

		TEST_CASE("Adding a first surface does not set the current surface", "[Services][SurfaceService]") {
			SurfaceService service;

			PathSurfaceMock surfaceMock;
			surfaceMock.name = "TEST";

			service.addSurface(&surfaceMock);

			REQUIRE_THROWS_AS(service.getCurrentSurface(), SurfaceNotFoundException);
		}

		TEST_CASE("Adding a surface then setting it as the current surface sets the surface", "[Services][SurfaceService]") {
			SurfaceService service;

			PathSurfaceMock surfaceMock;
			surfaceMock.name = "TEST";

			service.addSurface(&surfaceMock);
			service.setCurrentSurface(surfaceMock.name);

			IPathSurface& surface = service.getCurrentSurface();

			REQUIRE(surfaceMock.name == surface.getSurfaceName());
		}

		TEST_CASE("Removing a surface removes it as the current surface if it is", "[Services][SurfaceService]") {
			SurfaceService service;

			PathSurfaceMock surfaceMock;
			surfaceMock.name = "TEST";

			service.addSurface(&surfaceMock);
			service.setCurrentSurface(surfaceMock.name);
			REQUIRE(surfaceMock.name == service.getCurrentSurface().getSurfaceName());
			service.removeSurface(surfaceMock.name);

			REQUIRE_THROWS_AS(service.getCurrentSurface(), SurfaceNotFoundException);
		}
	}
}
