#ifndef INCLUDED_INTRUSION_INFRASTRUCTURE_INTRUSION_DEFINITIONS_HPP_
#define INCLUDED_INTRUSION_INFRASTRUCTURE_INTRUSION_DEFINITIONS_HPP_

namespace itr {
	
	class Definitions {
		Definitions(void) = delete;
		~Definitions(void) = delete;
	public:
		static constexpr const float TileSize = 1.0f;

		static constexpr const int Tile_Basic_Empty = 0;
		static constexpr const int Tile_Basic_Full = 1;
		static constexpr const int Tile_Basic_Start = 8;
		static constexpr const int Tile_Basic_End = 7;

		static constexpr const char LevelParseLuaStateScope[] = "LuaLevelParseScope";

		static constexpr const char TerrainTextureName[] = "terrain";
		static constexpr const char SpearIconTextureName[] = "spear_icon";
	};

}

#endif // INCLUDED_INTRUSION_INFRASTRUCTURE_INTRUSION_DEFINITIONS_HPP_