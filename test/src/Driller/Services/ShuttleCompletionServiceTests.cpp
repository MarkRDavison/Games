#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/ShuttleCompletionService.hpp>
#include <Mocks/Driller/Services/MarketServiceMock.hpp>
#include <Mocks/Driller/Services/ShuttleDepartureServiceMock.hpp>

namespace drl {
	namespace ShuttleCompletionServiceTests {
		
		struct Package {

			Package(void) :
				service(data, marketService, shuttleDepartureService) {
				
			}

			ShuttleData data{};
			MarketServiceMock marketService;
			ShuttleDepartureServiceMock shuttleDepartureService;
			ShuttleCompletionService service;
		};

		TEST_CASE("handleShuttleCompleted sets shuttle to require removal", "[Driller][Services][ShuttleCompletionService]") {
			Package package{};

			ShuttleInstance& instance = package.data.shuttles.emplace_back();

			package.service.handleShuttleCompleted(instance);

			REQUIRE(instance.removalRequired);
		}

		TEST_CASE("cleanupCompletedShuttles removes shuttles that require removal", "[Driller][Services][ShuttleCompletionService]") {
			Package package{};

			ShuttleInstance& instance = package.data.shuttles.emplace_back();

			package.service.handleShuttleCompleted(instance);
			package.service.cleanupCompletedShuttles();

			REQUIRE(package.data.shuttles.empty());
		}

		TEST_CASE("handleShuttleCompleted sells cargo to the market service", "[Driller][Services][ShuttleCompletionService]") {
			Package package{};

			const std::string ResourceName = Definitions::OreResourceName;
			const int ResourceAmount = 512;
			ShuttleInstance& instance = package.data.shuttles.emplace_back();
			instance.cargo.resources.emplace_back(ResourceName, ResourceAmount);

			bool sellCargoInvoked = false;
			package.marketService.sellCargoCallback = [&](const inf::ResourceBundle& _cargo) -> void {
				REQUIRE(1 == _cargo.resources.size());
				REQUIRE(ResourceName == _cargo.resources[0].name);
				REQUIRE(ResourceAmount == _cargo.resources[0].amount);
				sellCargoInvoked = true;
			};

			package.service.handleShuttleCompleted(instance);
			
			REQUIRE(sellCargoInvoked);
		}

		TEST_CASE("handleShuttleCompleted sets on run to false in shuttle departure service", "[Driller][Services][ShuttleCompletionService]") {
			Package package{};

			bool setShuttleOnRunInvoked = false;
			package.shuttleDepartureService.setShuttleOnRunCallback = [&](bool _onRun) -> void {
				REQUIRE_FALSE(_onRun);
				setShuttleOnRunInvoked = true;
			};

			ShuttleInstance instance{};

			package.service.handleShuttleCompleted(instance);

			REQUIRE(setShuttleOnRunInvoked);
		}
	}
}
