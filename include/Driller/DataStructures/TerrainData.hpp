#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_TERRAIN_DATA_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_TERRAIN_DATA_HPP_

#include <Driller/DataStructures/TerrainRow.hpp>
#include <exception>
#include <cmath>

namespace drl {

	struct TerrainData {
		
		std::vector<TerrainRow> rows;

		bool tileExists(int _level, int _column) const {
			if (_column == 0) {
				return false;
			}
			const unsigned xCoord = static_cast<unsigned>(std::abs(_column) - 1);
			if (_level >= static_cast<int>(rows.size())) {
				return false;
			}
			const TerrainRow& row = rows[static_cast<unsigned>(_level)];

			if (_column > 0) {
				if (static_cast<int>(row.rightTiles.size()) > xCoord) {
					return true;
				}
			} else {
				if (static_cast<int>(row.leftTiles.size()) > xCoord) {
					return true;
				}
			}

			return false;
		}

		const TerrainTile& getTile(int _level, int _column) const {
			const unsigned xCoord = static_cast<unsigned>(std::abs(_column)) - (_column == 0 ? 0 : 1);
			if (_column < 0) {
				return rows[static_cast<unsigned>(_level)].leftTiles[xCoord];
			}
			if (_column > 0) {
				return rows[static_cast<unsigned>(_level)].rightTiles[xCoord];
			}
			throw std::runtime_error("Cannot retrieve shaft TerrainTile");
		}

		TerrainTile& getTile(int _level, int _column) {
			const unsigned xCoord = static_cast<unsigned>(std::abs(_column)) - (_column == 0 ? 0 : 1);
			if (_column < 0) {
				return rows[static_cast<unsigned>(_level)].leftTiles[xCoord];
			}
			if (_column > 0) {
				return rows[static_cast<unsigned>(_level)].rightTiles[xCoord];
			}
			throw std::runtime_error("Cannot retrieve shaft TerrainTile");
		}



	};
	
}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_TERRAIN_DATA_HPP_