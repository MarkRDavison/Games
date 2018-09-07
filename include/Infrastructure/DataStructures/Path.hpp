#ifndef INCLUDED_INFRASTRUCTURE_DATA_STRUCTURES_PATH_HPP_
#define INCLUDED_INFRASTRUCTURE_DATA_STRUCTURES_PATH_HPP_

#include <Infrastructure/DataStructures/PathNode.hpp>
#include <vector>

namespace inf {
	
	struct Path {
		std::vector<PathNode> nodes;
		bool isValid;

	};

}

#endif // INCLUDED_INFRASTRUCTURE_DATA_STRUCTURES_PATH_HPP_