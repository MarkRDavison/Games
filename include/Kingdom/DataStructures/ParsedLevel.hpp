#ifndef INCLUDED_KINGDOM_DATA_STRUCTURES_PARSED_LEVEL_HPP_
#define INCLUDED_KINGDOM_DATA_STRUCTURES_PARSED_LEVEL_HPP_

#include <vector>
#include <Kingdom/DataStructures/LevelCell.hpp>

namespace kdm {

	struct ParsedLevel {
		unsigned width;
		unsigned height;
		std::string name;
		std::vector<kdm::LevelCell> levelCells;
	};

}

#endif // INCLUDED_KINGDOM_DATA_STRUCTURES_PARSED_LEVEL_HPP_