#ifndef INCLUDED_KINGDOM_DATA_STRUCTURES_PATH_HPP_
#define INCLUDED_KINGDOM_DATA_STRUCTURES_PATH_HPP_

#include <Kingdom/DataStructures/PathNode.hpp>
#include <vector>

namespace kdm {
	
	struct Path {
		std::vector<PathNode> nodes;
		bool isValid;

	};

}

#endif // INCLUDED_KINGDOM_DATA_STRUCTURES_PATH_HPP_