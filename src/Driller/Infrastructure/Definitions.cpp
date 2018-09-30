#include <Driller/Infrastructure/Definitions.hpp>

namespace drl {

	constexpr const char Definitions::OreResourceName[];
	constexpr const char Definitions::MoneyResourceName[];
	constexpr const char Definitions::MaxWorkerResourceName[];
	constexpr const char Definitions::CurrentWorkerResourceName[];

	constexpr const char Definitions::TileSpriteSheetTextureName[];

	constexpr const char Definitions::Building1PrototypeName[];
	constexpr const char Definitions::Building2PrototypeName[];
	constexpr const char Definitions::Building3PrototypeName[];
	constexpr const char Definitions::Building4PrototypeName[];
	constexpr const char Definitions::Building5PrototypeName[];

	constexpr const char Definitions::JobPrototypeName_Dig[];

	constexpr const char Definitions::WorkerPrototypeName_All[];

	const sf::Vector2u Definitions::OneBuildingCoordinate	{ 2, 0 };
	const sf::Vector2u Definitions::TwoBuildingCoordinate	{ 2, 1 };
	const sf::Vector2u Definitions::ThreeBuildingCoordinate	{ 2, 2 };
	const sf::Vector2u Definitions::FourBuildingCoordinate	{ 2, 3 };
	const sf::Vector2u Definitions::FiveBuildingCoordinate	{ 2, 4 };

	const sf::Vector2u Definitions::DigJobCoordinate		{ 1, 1 };

	const sf::Vector2f Definitions::ShuttleLandingCoordinates{ -5.0f, GroundLevel };;

}