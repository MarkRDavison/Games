#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_BUILDING_PLACEMENT_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_BUILDING_PLACEMENT_SERVICE_HPP_
#include <Driller/DataStructures/GameCommand.hpp>
#include <Driller/DataStructures/BuildingPrototype.hpp>

namespace drl {

	class IBuildingPlacementService {
	public:
		virtual ~IBuildingPlacementService(void) = 0 {}

		virtual bool canPlacePrototype(const GameCommand::PlaceBuildingEvent& _placeBuilding) = 0;
		virtual bool canPlacePrototype(const BuildingPrototypeId& _prototypeId, int _level, int _column) = 0;
		virtual void placePrototype(const GameCommand::PlaceBuildingEvent& _placeBuilding) = 0;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_BUILDING_PLACEMENT_SERVICE_HPP_