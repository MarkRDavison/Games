#include <Driller/Infrastructure/Definitions.hpp>

namespace drl {

	constexpr const char Definitions::OreResourceName[];
	constexpr const char Definitions::OreExchangeRateResourceName[];
	constexpr const char Definitions::MoneyResourceName[];

	constexpr const char Definitions::CurrentWorkerResourceName[];

	constexpr const char Definitions::CurrentBuilderResourceName[];
	constexpr const char Definitions::CurrentMinerResourceName[];
	constexpr const char Definitions::CurrentRefinerResourceName[];

	constexpr const char Definitions::TileSpriteSheetTextureName[];

	constexpr const char Definitions::BuildingBunkPrototypeName[];
	constexpr const char Definitions::BuildingBuilderPrototypeName[];
	constexpr const char Definitions::BuildingMinerPrototypeName[];
	constexpr const char Definitions::BuildingRefinerPrototypeName[];

	constexpr const char Definitions::JobPrototypeName_Dig[];
	constexpr const char Definitions::JobPrototypeName_BuildBuilding[]; 
	constexpr const char Definitions::JobPrototypeName_Miner[];
	constexpr const char Definitions::JobPrototypeName_Refiner[];

	constexpr const char Definitions::WorkerPrototypeName_Builder[];
	constexpr const char Definitions::WorkerPrototypeName_Miner[];
	constexpr const char Definitions::WorkerPrototypeName_Refiner[];

	constexpr const char Definitions::ShuttlePrototypeName_Starting[];

	const sf::Vector2u Definitions::BunkBuildingCoordinate		{ 3, 0 };
	const sf::Vector2u Definitions::BuilderBuildingCoordinate	{ 5, 0 };
	const sf::Vector2u Definitions::MinerBuildingCoordinate		{ 7, 0 };
	const sf::Vector2u Definitions::RefinerBuildingCoordinate	{ 10, 0 };

	const sf::Vector2u Definitions::DigJobCoordinate		{ 1, 1 };

	const sf::Vector2f Definitions::ShuttleStartingCoordinates{ -15.0f, -10.0f};
	const sf::Vector2f Definitions::ShuttleLandingCoordinates{ -5.0f, GroundLevel };;
	const sf::Vector2f Definitions::ShuttleEndingCoordinates{ +25.0f, -5.0f };

}