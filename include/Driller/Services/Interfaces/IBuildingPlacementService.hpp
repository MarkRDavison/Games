#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_BUILDING_PLACEMENT_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_BUILDING_PLACEMENT_SERVICE_HPP_

#include <Driller/DataStructures/GameCommand.hpp>
#include <Driller/DataStructures/BuildingInstance.hpp>
#include <Driller/DataStructures/BuildingPrototype.hpp>

namespace drl {

	class IBuildingPlacementService {
	public:
		virtual ~IBuildingPlacementService(void) = 0;

		virtual bool canPlacePrototype(const GameCommand::CommandContext _context, const GameCommand::PlaceBuildingEvent& _placeBuilding) = 0;
		virtual bool canPlacePrototype(const GameCommand::CommandContext _context, const BuildingPrototypeId& _prototypeId, int _level, int _column) = 0;
		virtual const BuildingInstance& placePrototype(const GameCommand::CommandContext _context, const GameCommand::PlaceBuildingEvent& _placeBuilding) = 0;
	};

	inline IBuildingPlacementService::~IBuildingPlacementService(void) = default;
}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_BUILDING_PLACEMENT_SERVICE_HPP_