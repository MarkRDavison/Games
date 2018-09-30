#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_TERRAIN_ROW_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_TERRAIN_ROW_HPP_

#include <Driller/DataStructures/TerrainTile.hpp>
#include <vector>

namespace drl {

	struct TerrainRow {

		std::vector<TerrainTile> leftTiles;
		std::vector<TerrainTile> rightTiles;

	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_TERRAIN_TINCLUDED_DRILLER_DATA_STRUCTURES_TERRAIN_ROW_HPP_ILE_HPP_