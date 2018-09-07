#ifndef INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_LEVEL_HPP_
#define INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_LEVEL_HPP_

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <Intrusion/DataStructures/LevelCell.hpp>
#include <Intrusion/DataStructures/ParsedWave.hpp>

namespace itr {

	struct ParsedLevel {
		unsigned width;
		unsigned height;
		std::string name;
		std::vector<LevelCell> levelCells;
		std::vector<WaveInstance> waves;
		sf::Vector2i start;
		sf::Vector2i end;
	};

}

#endif // INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_LEVEL_HPP_