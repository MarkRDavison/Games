#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/MarketService.hpp>
#include <Mocks/Infrastructure/Services/ResourceServiceMock.hpp>

namespace drl {
	namespace MarketServiceTests {

		struct Package {
			
			Package(void) :
				service(resourceService) {
				
			}

			inf::ResourceServiceMock resourceService;
			MarketService service;

		};
		
		TEST_CASE("sellCargo invokes pay resource bundle on the resource service", "[Driller][Services][MarketService]") {
			Package package{};

			inf::ResourceBundle resourceBundle{};

			bool payResourceBundleInvoked = false;
			package.resourceService.payResourceBundleCallback = [&](const inf::ResourceBundle& _resourceBundle) -> void {
				REQUIRE(&resourceBundle == &_resourceBundle);
				payResourceBundleInvoked = true;
			};

			package.service.sellCargo(resourceBundle);

			REQUIRE(payResourceBundleInvoked);
		}

	}
}
