#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_TERRAIN_TILE_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_TERRAIN_TILE_HPP_

namespace drl {
	
	struct TerrainTile {

		bool dugOut{ false };
		bool jobReserved{ false };
		bool hasBuilding{ false };

	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_TERRAIN_TILE_HPP_