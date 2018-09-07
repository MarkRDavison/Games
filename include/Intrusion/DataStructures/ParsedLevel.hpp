#ifndef INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_LEVEL_HPP_
#define INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_LEVEL_HPP_

#include <vector>
#include <Intrusion/DataStructures/LevelCell.hpp>

namespace itr {

	struct ParsedLevel {
		unsigned width;
		unsigned height;
		std::string name;
		std::vector<LevelCell> levelCells;
	};

}

#endif // INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_LEVEL_HPP_