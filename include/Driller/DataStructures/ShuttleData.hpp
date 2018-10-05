#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_SHUTTLE_DATA_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_SHUTTLE_DATA_HPP_

#include <Driller/DataStructures/ShuttleInstance.hpp>
#include <vector>

namespace drl {
	
	struct ShuttleData {
		std::vector<ShuttleInstance> shuttles;
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_SHUTTLE_DATA_HPP_