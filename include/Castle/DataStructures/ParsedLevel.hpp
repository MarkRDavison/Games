#ifndef INCLUDED_CASTLE_DATA_STRUCTURES_PARSED_LEVEL_HPP_
#define INCLUDED_CASTLE_DATA_STRUCTURES_PARSED_LEVEL_HPP_

#include <Castle/DataStructures/LevelCell.hpp>
#include <Castle/DataStructures/ParsedEntity.hpp>
#include <vector>

namespace castle {
	
	struct ParsedLevel {

		static ParsedLevel createTestLevel(void) {
			ParsedLevel l;
			l.width = 23;
			l.height = 13;
			
			l.levelCells = std::vector<LevelCell>(l.width * l.height);
			for (unsigned y = 0u; y < l.height; ++y ) {
				for (unsigned x = 0u; x < l.width; ++x) {
					if (y == 0u || x == 0u || y == l.height - 1 || x == l.width - 1) {
						l.levelCells[y * l.width + x].empty = false;
					} else {
						l.levelCells[y * l.width + x].empty = true;
					}
				}
			}
			l.levelCells[10 * l.width + 1].empty = false;
			l.levelCells[10 * l.width + 2].empty = false;

			l.levelCells[9 * l.width + 5].empty = false;
			l.levelCells[9 * l.width + 6].empty = false;

			l.levelCells[6 * l.width + 5].empty = false;
			l.levelCells[6 * l.width + 6].empty = false;

			l.levelCells[4 * l.width + 1].empty = false;
			l.levelCells[4 * l.width + 2].empty = false;

			l.levelCells[8 * l.width + 9].empty = false;
			l.levelCells[8 * l.width + 10].empty = false;

			l.levelCells[9 * l.width + 21].empty = false;
			l.levelCells[8 * l.width + 20].empty = false;
			l.levelCells[8 * l.width + 19].empty = false;
			l.levelCells[8 * l.width + 18].empty = false;
			l.levelCells[8 * l.width + 17].empty = false;
			l.levelCells[9 * l.width + 17].empty = false;

			l.levelCells[4 * l.width + 18].empty = false;
			l.levelCells[4 * l.width + 17].empty = false;

			return l;
		}

		unsigned width;
		unsigned height;
		std::string name;
		std::vector<LevelCell> levelCells;
		std::vector<ParsedEntity> entities;
	};

}

#endif // INCLUDED_CASTLE_DATA_STRUCTURES_PARSED_LEVEL_HPP_