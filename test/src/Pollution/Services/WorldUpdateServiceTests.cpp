#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Pollution/Services/WorldUpdateService.hpp>
#include <Mocks/Infrastructure/Services/ResourceServiceMock.hpp>

namespace pol {
	namespace WorldUpdateServiceTests {

		TEST_CASE("updating service rotates the world", "[Pollution][Services][WorldUpdateService]") {
			const float RotationRate = 90.0f;
			const float Delta = 1.0f;

			WorldData data{};
			data.rotationRate = RotationRate;

			inf::ResourceServiceMock resourceService;
			WorldUpdateService service(resourceService);

			service.update(Delta, data);

			REQUIRE(Delta * RotationRate == data.rotation);
		}

		TEST_CASE("updating service keeps rotation within 0 - 360", "[Pollution][Services][WorldUpdateService]") {
			const float RotationRate = 450.0f;
			const float Delta = 1.0f;

			WorldData data{};
			data.rotationRate = RotationRate;

			inf::ResourceServiceMock resourceService;
			WorldUpdateService service(resourceService);

			service.update(Delta, data);

			REQUIRE(Delta * (RotationRate - 360.0f) == data.rotation);
		}

		TEST_CASE("updating service increase accumulated drop time for buildings", "[Pollution][Services][WorldUpdateService]") {
			const float Delta = 1.0f;

			WorldData data{};
			data.Sides = 1;
			data.buildings.emplace_back();

			BuildingData& building = data.buildings.back();
			building.active = true;
			building.dropRate = Delta * 10.0f;

			inf::ResourceServiceMock resourceService;
			WorldUpdateService service(resourceService);

			service.update(Delta, data);

			REQUIRE(Delta == building.accumulatedDropTime);
		}

		TEST_CASE("updating service increase accumulated animation time for buildings", "[Pollution][Services][WorldUpdateService]") {
			const float Delta = 1.0f;

			WorldData data{};
			data.Sides = 1;
			data.buildings.emplace_back();

			BuildingData& building = data.buildings.back();
			building.active = true;

			inf::ResourceServiceMock resourceService;
			WorldUpdateService service(resourceService);

			service.update(Delta, data);

			REQUIRE(Delta == building.accumulatedAnimationTime);
		}

		TEST_CASE("updating service for active building over drop rate increases resources by drops bundle", "[Pollution][Services][WorldUpdateService]") {
			const float Delta = 2.0f;

			WorldData data{};
			data.Sides = 1;
			data.buildings.emplace_back();

			BuildingData& building = data.buildings.back();
			building.dropRate = Delta;
			building.active = true;
			inf::ResourceBundle *rb = &building.drops;

			inf::ResourceServiceMock resourceService;
			WorldUpdateService service(resourceService);

			bool receiveResourceBundleInvoked = false;
			resourceService.receiveResourceBundleCallback = [&](const inf::ResourceBundle& _bundle) {
				REQUIRE(rb == &_bundle);
				receiveResourceBundleInvoked = true;
			};

			service.update(Delta, data);

			REQUIRE(receiveResourceBundleInvoked);
			REQUIRE(0.0f == building.accumulatedDropTime);
		}

		TEST_CASE("updating service for inactive building does not increase the accumulated drop time", "[Pollution][Services][WorldUpdateService]") {
			const float Delta = 2.0f;

			WorldData data{};
			data.Sides = 1;
			data.buildings.emplace_back();

			BuildingData& building = data.buildings.back();
			building.dropRate = Delta * 2.0f;
			building.active = false;

			inf::ResourceServiceMock resourceService;
			WorldUpdateService service(resourceService);

			service.update(Delta, data);

			REQUIRE(0.0f == building.accumulatedDropTime);
		}
	}
}
