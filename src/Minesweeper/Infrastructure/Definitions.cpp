#include <Minesweeper/Infrastructure/Definitions.hpp>

namespace swp {

	constexpr const char Definitions::GameLuaScope[];

	constexpr const char Definitions::CellSpriteSheetTextureName[];
	constexpr const char Definitions::FaceSpriteSheetTextureName[];

	const sf::Vector2i Definitions::HappyFaceTileCoords =	{ 0, 0 };
	const sf::Vector2i Definitions::WinceFaceTileCoords =	{ 1, 0 };
	const sf::Vector2i Definitions::WinFaceTileCoords =		{ 2, 0 };
	const sf::Vector2i Definitions::LoseFaceTileCoords =	{ 3, 0 };

	const sf::Vector2i Definitions::InvalidCellCoordinates = { -1, -1 };
}