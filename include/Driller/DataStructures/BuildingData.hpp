#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_DATA_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_DATA_HPP_

#include <Driller/DataStructures/BuildingInstance.hpp>
#include <vector>

namespace drl {
	
	struct BuildingData {
		std::vector<BuildingInstance> buildings;
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_DATA_HPP_