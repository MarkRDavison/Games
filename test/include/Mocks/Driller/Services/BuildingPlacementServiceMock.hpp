#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_BUILDING_PLACEMENT_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_BUILDING_PLACEMENT_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IBuildingPlacementService.hpp>
#include <functional>

namespace drl {
	
	class BuildingPlacementServiceMock : public IBuildingPlacementService {
	public:
		~BuildingPlacementServiceMock(void) override {}

		bool canPlacePrototype(const GameCommand::CommandContext _context, const BuildingPrototypeId& _prototypeId, int _level, int _column) override {
			GameCommand::PlaceBuildingEvent event{};
			event.prototypeId = _prototypeId;
			event.column = _column;
			event.level = _level;
			return canPlacePrototype(_context, event);
		}
		bool canPlacePrototype(const GameCommand::CommandContext _context, const GameCommand::PlaceBuildingEvent& _placeBuilding) override {
			if (canPlacePrototypeCallback) {
				return canPlacePrototypeCallback(_context, _placeBuilding);
			}

			return false;
		}

		void placePrototype(const GameCommand::CommandContext _context, const GameCommand::PlaceBuildingEvent& _placeBuilding) override {
			if (placePrototypeCallback) {
				placePrototypeCallback(_context, _placeBuilding);
			}
		}

		std::function<bool(const GameCommand::CommandContext, const GameCommand::PlaceBuildingEvent&)> canPlacePrototypeCallback;
		std::function<void(const GameCommand::CommandContext, const GameCommand::PlaceBuildingEvent&)> placePrototypeCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_BUILDING_PLACEMENT_SERVICE_MOCK_HPP_