#ifndef INCLUDED_INTRUSION_INFRASTRUCTURE_INTRUSION_DEFINITIONS_HPP_
#define INCLUDED_INTRUSION_INFRASTRUCTURE_INTRUSION_DEFINITIONS_HPP_

namespace itr {
	
	class Definitions {
		Definitions(void) = delete;
		~Definitions(void) = delete;
	public:
		static constexpr const float TileSize = 1.0f;
		static constexpr const float HalfTileSize = TileSize / 2.0f;
		static constexpr const float DefaultTowerRange = 2.0f;

		static constexpr const int Tile_Basic_Empty = 0;
		static constexpr const int Tile_Basic_Full = 1;
		static constexpr const int Tile_Basic_Start = 8;
		static constexpr const int Tile_Basic_End = 7;

		static constexpr const int DefaultResourceMaximum = -1;
		static constexpr const int DefaultLivesResourceAmount = 10;
		static constexpr const int DefaultGoldResourceAmount = 250;


		static constexpr const char EntityParseLuaStateScope[] = "LuaEntityParseScope";
		static constexpr const char LevelParseLuaStateScope[] = "LuaLevelParseScope";
		static constexpr const char TowerParseLuaStateScope[] = "LuaTowerParseScope";

		static constexpr const char TerrainTextureName[] = "terrain";
		static constexpr const char SpearIconTextureName[] = "spear_icon";
		static constexpr const char MissingTextureName[] = "missing";
		static constexpr const char StarTowerTextureName[] = "star_greyscale_tower";

		static constexpr const char LivesResourceName[] = "lives";
		static constexpr const char GoldResourceName[] = "gold";
		static constexpr const char KillsResourceName[] = "kills";

		static constexpr const char DefaultEntityPrototypeName[] = "Default_Entity";
		static constexpr const char DefaultTowerPrototypeName[] = "Default_Tower";
		static constexpr const char DefaultAnimationName[] = "missing";
		static constexpr const float DefaultEntitySpeed{ 1.0f };
		static constexpr const float DefaultIntervalRange{ 0.1f };
		static constexpr const float DefaultEntityHealth{ 10.0f };
	};

}

#endif // INCLUDED_INTRUSION_INFRASTRUCTURE_INTRUSION_DEFINITIONS_HPP_