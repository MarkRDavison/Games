#ifndef INCLUDED_KINGDOM_INFRASTRUCTURE_DEFINITIONS_HPP_
#define INCLUDED_KINGDOM_INFRASTRUCTURE_DEFINITIONS_HPP_

namespace kdm {
	
	class Definitions {
	public:
		Definitions(void) = delete;
		~Definitions(void) = delete;

		static constexpr const float TileSize = 1.0f;

		static constexpr const char TerrainTextureName[] = "terrain";
		static constexpr const char GearTextureName[] = "gear";
		static constexpr const char UiLuaStateScope[] = "UiLuaStateScope";
		static constexpr const char LevelParseLuaStateScope[] = "LevelParseLuaStateScope";
	};

}

#endif // INCLUDED_KINGDOM_INFRASTRUCTURE_DEFINITIONS_HPP_