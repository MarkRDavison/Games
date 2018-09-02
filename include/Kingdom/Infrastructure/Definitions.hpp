#ifndef INCLUDED_KINGDOM_INFRASTRUCTURE_DEFINITIONS_HPP_
#define INCLUDED_KINGDOM_INFRASTRUCTURE_DEFINITIONS_HPP_

namespace kdm {
	
	class Definitions {
	public:
		Definitions(void) = delete;
		~Definitions(void) = delete;

		static constexpr const float TileSize = 1.0f;

		static const char *TerrainTextureName;
		static const char *GearTextureName;
		static const char *UiLuaStateScope;
		static const char *LevelParseLuaStateScope;
	};

}

#endif // INCLUDED_KINGDOM_INFRASTRUCTURE_DEFINITIONS_HPP_