#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/CostService.hpp>

namespace drl {
	namespace CostServiceTests {
		
		struct Package {
			
			Package(void) :
				service() {
				
			}

			CostService service;
		};

		TEST_CASE("getDigShaftCost increases as level increases", "[Driller][Services][CostService]") {
			Package package{};

			const int level1cost = package.service.getDigShaftCost(1);
			const int level2cost = package.service.getDigShaftCost(2);
			const int level3cost = package.service.getDigShaftCost(3);
			const int level4cost = package.service.getDigShaftCost(4);

			REQUIRE(level1cost < level2cost);
			REQUIRE(level2cost < level3cost);
			REQUIRE(level3cost < level4cost);
		}
	}
} 