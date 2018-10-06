#ifndef INCLUDED_DRILLER_INFRASTRUCTURE_DEFINITIONS_HPP_
#define INCLUDED_DRILLER_INFRASTRUCTURE_DEFINITIONS_HPP_

#include <cstdlib>
#include <SFML/System/Vector2.hpp>

namespace drl {

	using EntityId = std::size_t;

	class Definitions {
		Definitions(void) = delete;
		~Definitions(void) = delete;
	public:

		static constexpr const char OreResourceName[] = "Ore";
		static constexpr const char MoneyResourceName[] = "Money";

		static constexpr const char CurrentWorkerResourceName[] = "CurrentWorker";

		static constexpr const char CurrentBuilderResourceName[] = "CurrentBuilder";
		static constexpr const char CurrentMinerResourceName[] = "CurrentMiner";

		static constexpr const char TileSpriteSheetTextureName[] = "tile_sprite_sheet";

		static constexpr const char Building1PrototypeName[] = "One";
		static constexpr const char Building2PrototypeName[] = "Two";
		static constexpr const char Building3PrototypeName[] = "Three";
		static constexpr const char Building4PrototypeName[] = "Four";
		static constexpr const char Building5PrototypeName[] = "Five";

		static constexpr const char BuildingBunkPrototypeName[] = "Building_Bunk";
		static constexpr const char BuildingBuilderPrototypeName[] = "Building_Builder";
		static constexpr const char BuildingMinerPrototypeName[] = "Building_Miner";

		static constexpr const char JobPrototypeName_Dig[] = "Job_Dig";
		static constexpr const char JobPrototypeName_BuildBuilding[] = "Job_BuildBuilding";
		static constexpr const char JobPrototypeName_Miner[] = "Job_Miner";

		static constexpr const char WorkerPrototypeName_Builder[] = "Worker_Builder";
		static constexpr const char WorkerPrototypeName_Miner[] = "Worker_Miner";

		static constexpr const char ShuttlePrototypeName_Starting[] = "Shuttle_Starting";

		static constexpr const float TileSize{ 1.0f };
		static constexpr const float GroundLevel{ -1.0f };
		static constexpr const float BaseShuttleSpeed{ 5.0f };
		static constexpr const float BaseWorkerSpeed{ 2.0f };

		static const sf::Vector2u OneBuildingCoordinate;
		static const sf::Vector2u TwoBuildingCoordinate;
		static const sf::Vector2u ThreeBuildingCoordinate;
		static const sf::Vector2u FourBuildingCoordinate;
		static const sf::Vector2u FiveBuildingCoordinate;
		static const sf::Vector2u BunkBuildingCoordinate;
		static const sf::Vector2u BuilderBuildingCoordinate;
		static const sf::Vector2u MinerBuildingCoordinate;

		static const sf::Vector2u DigJobCoordinate;

		static const sf::Vector2f ShuttleStartingCoordinates;
		static const sf::Vector2f ShuttleLandingCoordinates;
		static const sf::Vector2f ShuttleEndingCoordinates;

		enum class GameSceneState {
			Title,
			Gameplay,
			Exit,

			Invalid
		};

	};

}

#endif // INCLUDED_DRILLER_INFRASTRUCTURE_DEFINITIONS_HPP_