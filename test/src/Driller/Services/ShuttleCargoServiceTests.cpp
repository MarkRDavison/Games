#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/ShuttleCargoService.hpp>
#include <Mocks/Infrastructure/Services/ResourceServiceMock.hpp>

namespace drl {
	namespace ShuttleCargoServiceTests {

		struct Package {

			Package() :
				service(resourceService) {
				
			}
			
			inf::ResourceServiceMock resourceService;

			ShuttleCargoService service;

		};
		
		TEST_CASE("loadShuttleWithCargo asks the resource service for any ore present", "[Driller][Services][ShuttleCargoService]") {
			Package package{};

			ShuttleInstance instance{};

			bool getResourceCallbackInvoked = false;
			package.resourceService.getResourceCallback = [&](const std::string& _resource) -> int {
				REQUIRE(Definitions::OreResourceName == _resource);
				getResourceCallbackInvoked = true;
				return 0;
			};

			package.service.loadShuttleWithCargo(instance);

			REQUIRE(getResourceCallbackInvoked);
		}

		TEST_CASE("loadShuttleWithCargo doesnt reduce the ore resource if there is 0 ore available", "[Driller][Services][ShuttleCargoService]") {
			Package package{};

			ShuttleInstance instance{};

			bool updateResourceCallbackInvoked = false;
			package.resourceService.getResourceCallback = [&](const std::string& _resource) -> int { return 0; };
			package.resourceService.updateResourceCallback = [&](const std::string&, int) -> void {
				updateResourceCallbackInvoked = true;
			};

			package.service.loadShuttleWithCargo(instance);

			REQUIRE_FALSE(updateResourceCallbackInvoked);
		}

		TEST_CASE("loadShuttleWithCargo does reduce the ore resource if there is more than 0 ore available", "[Driller][Services][ShuttleCargoService]") {
			Package package{};

			const int OreAvailable = 5;
			ShuttleInstance instance{};

			bool updateResourceCallbackInvoked = false;
			package.resourceService.getResourceCallback = [&](const std::string& _resource) -> int { return OreAvailable; };
			package.resourceService.updateResourceCallback = [&](const std::string& _resource, int _amount) -> void {
				REQUIRE(Definitions::OreResourceName == _resource);
				REQUIRE(-OreAvailable == _amount);
				updateResourceCallbackInvoked = true;
			};

			package.service.loadShuttleWithCargo(instance);

			REQUIRE(updateResourceCallbackInvoked);
		}

		TEST_CASE("loadShuttleWithCargo moves the ore into the shuttles cargo", "[Driller][Services][ShuttleCargoService]") {
			Package package{};

			const int OreAvailable = 5;
			ShuttleInstance instance{};

			package.resourceService.getResourceCallback = [&](const std::string& _resource) -> int { return OreAvailable; };
			
			package.service.loadShuttleWithCargo(instance);

			REQUIRE(1 == instance.cargo.resources.size());
			REQUIRE(Definitions::OreResourceName == instance.cargo.resources[0].name);
			REQUIRE(OreAvailable == instance.cargo.resources[0].amount);
		}

	}
}
