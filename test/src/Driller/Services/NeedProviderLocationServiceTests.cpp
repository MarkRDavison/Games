#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/NeedProviderLocationService.hpp>

namespace drl {
	namespace NeedProviderLocationServiceTests {

		struct Package {

			Package(void) :
				service(buildingData) {

			}
			BuildingData buildingData;
			NeedProviderLocationService service;

		};

		TEST_CASE("isNeedProviderAvailable returns false when no buildings provide the need", "[Driller][Services][NeedProviderLocationService]") {
			Package package{};

			const std::size_t NeedId = 1u;

			REQUIRE_FALSE(package.service.isNeedProviderAvailable(NeedId));
		}

		TEST_CASE("isNeedProviderAvailable returns true when building provides the need", "[Driller][Services][NeedProviderLocationService]") {
			Package package{};

			const std::size_t NeedId = 1u;
			BuildingInstance& building = package.buildingData.buildings.emplace_back();
			building.providesNeeds = true;
			building.providedNeedId = NeedId;
			building.providedNeeds.emplace_back();

			REQUIRE(package.service.isNeedProviderAvailable(NeedId));
		}

		TEST_CASE("isNeedProviderAvailable returns false when building provides the need but worker is already allocated", "[Driller][Services][NeedProviderLocationService]") {
			Package package{};

			const std::size_t NeedId = 1u;
			BuildingInstance& building = package.buildingData.buildings.emplace_back();
			building.providesNeeds = true;
			building.providedNeedId = NeedId;
			BuildingProvidedNeed& providedNeed = building.providedNeeds.emplace_back();
			providedNeed.allocatedWorkerId = 1u;

			REQUIRE_FALSE(package.service.isNeedProviderAvailable(NeedId));
		}

		TEST_CASE("getNeedProvider returns correct provider entity when no buildings provide the need", "[Driller][Services][NeedProviderLocationService]") {
			Package package{};

			const std::size_t NeedId = 1u;

			REQUIRE(0u == package.service.getNeedProvider(NeedId, {}));
		}

		TEST_CASE("getNeedProvider returns correct provider entity when building provides the need", "[Driller][Services][NeedProviderLocationService]") {
			Package package{};

			const std::size_t NeedId = 1u;
			BuildingInstance& building = package.buildingData.buildings.emplace_back();
			building.Id = 44u;
			building.providesNeeds = true;
			building.providedNeedId = NeedId;
			building.providedNeeds.emplace_back();

			REQUIRE(building.Id == package.service.getNeedProvider(NeedId, {}));
		}

		TEST_CASE("getNeedProvider returns correct provider entity when building provides the need but worker is already allocated", "[Driller][Services][NeedProviderLocationService]") {
			Package package{};

			const std::size_t NeedId = 1u;
			BuildingInstance& building = package.buildingData.buildings.emplace_back();
			building.providesNeeds = true;
			building.providedNeedId = NeedId;
			BuildingProvidedNeed& providedNeed = building.providedNeeds.emplace_back();
			providedNeed.allocatedWorkerId = 1u;

			REQUIRE(0u == package.service.getNeedProvider(NeedId, {}));
		}

	}
}