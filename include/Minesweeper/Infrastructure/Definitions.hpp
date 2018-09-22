#ifndef INCLUDED_MINESWEEPER_INFRASTRUCTURE_DEFINITIONS_HPP_
#define INCLUDED_MINESWEEPER_INFRASTRUCTURE_DEFINITIONS_HPP_
#include <SFML/System/Vector2.hpp>

namespace swp {
	
	class Definitions {
	public:
		Definitions(void) = delete;
		~Definitions(void) = delete;

		static constexpr const char GameLuaScope[] = "GameLuaScope";

		static constexpr const char CellSpriteSheetTextureName[] = "cell_sprite_sheet";
		static constexpr const char FaceSpriteSheetTextureName[] = "face_sprite_sheet";

		static constexpr const float CellSize{ 1.0f };

		static const sf::Vector2i HappyFaceTileCoords;
		static const sf::Vector2i WinceFaceTileCoords;
		static const sf::Vector2i WinFaceTileCoords;
		static const sf::Vector2i LoseFaceTileCoords;
		
		static const sf::Vector2i InvalidCellCoordinates;
	};

}

#endif // INCLUDED_MINESWEEPER_INFRASTRUCTURE_DEFINITIONS_HPP_