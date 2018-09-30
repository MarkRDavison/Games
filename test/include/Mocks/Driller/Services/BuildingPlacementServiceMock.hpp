#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_BUILDING_PLACEMENT_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_BUILDING_PLACEMENT_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IBuildingPlacementService.hpp>
#include <functional>

namespace drl {
	
	class BuildingPlacementServiceMock : public IBuildingPlacementService {
	public:
		~BuildingPlacementServiceMock(void) override {}

		bool canPlacePrototype(const GameCommand::PlaceBuildingEvent& _placeBuilding) override {
			if (canPlacePrototypeCallback) {
				return canPlacePrototypeCallback(_placeBuilding);
			}

			return false;
		}

		void placePrototype(const GameCommand::PlaceBuildingEvent& _placeBuilding) override {
			if (placePrototypeCallback) {
				placePrototypeCallback(_placeBuilding);
			}
		}

		std::function<bool(const GameCommand::PlaceBuildingEvent&)> canPlacePrototypeCallback;
		std::function<void(const GameCommand::PlaceBuildingEvent&)> placePrototypeCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_BUILDING_PLACEMENT_SERVICE_MOCK_HPP_