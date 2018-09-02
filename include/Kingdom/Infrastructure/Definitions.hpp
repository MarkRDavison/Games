#ifndef INCLUDED_KINGDOM_INFRASTRUCTURE_DEFINITIONS_HPP_
#define INCLUDED_KINGDOM_INFRASTRUCTURE_DEFINITIONS_HPP_

namespace kdm {
	
	class Definitions {
	public:
		Definitions(void) = delete;
		~Definitions(void) = delete;

		static constexpr float TileSize{ 1.0f };

		static constexpr char *TerrainTextureName{ "terrain" };
		static constexpr char *GearTextureName{ "gear" };
		static constexpr char *UiLuaStateScope{ "UiLuaStateScope" };
		static constexpr char *LevelParseLuaStateScope{ "LevelParseLuaStateScope" };
	};

}

#endif // INCLUDED_KINGDOM_INFRASTRUCTURE_DEFINITIONS_HPP_