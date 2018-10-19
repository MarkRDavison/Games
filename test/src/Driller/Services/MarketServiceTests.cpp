#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/MarketService.hpp>
#include <Mocks/Infrastructure/Services/ResourceServiceMock.hpp>
#include <Driller/Infrastructure/Definitions.hpp>

namespace drl {
	namespace MarketServiceTests {

		struct Package {
			
			Package(void) :
				service(resourceService) {
				
			}

			inf::ResourceServiceMock resourceService;
			MarketService service;

		};
		
		TEST_CASE("sellCargo invokes receive resource bundle on the resource service", "[Driller][Services][MarketService]") {
			Package package{};

			const inf::ResourceBundle resourceBundle{};

			bool receiveResourceBundleInvoked = false;
			package.resourceService.receiveResourceBundleCallback = [&](const inf::ResourceBundle& _resourceBundle) -> void {
				receiveResourceBundleInvoked = true;
			};

			package.service.sellCargo(resourceBundle);

			REQUIRE(receiveResourceBundleInvoked);
		}

		TEST_CASE("applyExchangeRatesToBundle looks up the ore exchange rate", "[Driller][Services][MarketService]") {
			Package package{};

			const inf::ResourceBundle resourceBundle{};

			bool getResourceCallbackInvoked = false;
			package.resourceService.getResourceCallback = [&](const std::string& _resourceName) -> int {
				REQUIRE(Definitions::OreExchangeRateResourceName == _resourceName);
				getResourceCallbackInvoked = true;
				return 0;
			};

			package.service.applyExchangeRatesToBundle(resourceBundle);

			REQUIRE(getResourceCallbackInvoked);
		}

		TEST_CASE("applyExchangeRatesToBundle looks up the ore exchange rate and returns the resource bundle with the money amount the same as the ore with no exchange rate boost", "[Driller][Services][MarketService]") {
			Package package{};

			const int OreExchangeRate = 0;
			const int OreAmount = 100;
			inf::ResourceBundle resourceBundle{};
			resourceBundle.resources.emplace_back(Definitions::OreResourceName, OreAmount);

			package.resourceService.getResourceCallback = [&](const std::string& _resourceName) -> int { return OreExchangeRate; };

			const inf::ResourceBundle& exchangedBundle = package.service.applyExchangeRatesToBundle(resourceBundle);

			REQUIRE(1 == exchangedBundle.resources.size());
			REQUIRE(Definitions::MoneyResourceName == exchangedBundle.resources[0].name);
			REQUIRE(OreAmount == exchangedBundle.resources[0].amount);
		}

		TEST_CASE("applyExchangeRatesToBundle looks up the ore exchange rate and returns the resource bundle with the money amount altered by the exchanged rate", "[Driller][Services][MarketService]") {
			Package package{};

			const int OreExchangeRate = static_cast<float>(Definitions::OreExchangeRateScale);
			const int OreAmount = 100;
			inf::ResourceBundle resourceBundle{};
			resourceBundle.resources.emplace_back(Definitions::OreResourceName, OreAmount);

			package.resourceService.getResourceCallback = [&](const std::string& _resourceName) -> int { return OreExchangeRate; };

			const inf::ResourceBundle& exchangedBundle = package.service.applyExchangeRatesToBundle(resourceBundle);

			REQUIRE(1 == exchangedBundle.resources.size());
			REQUIRE(Definitions::MoneyResourceName == exchangedBundle.resources[0].name);
			REQUIRE(2 * OreAmount == exchangedBundle.resources[0].amount);
		}
	}
}
