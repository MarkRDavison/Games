#ifndef INCLUDED_DRILLER_INFRASTRUCTURE_DEFINITIONS_HPP_
#define INCLUDED_DRILLER_INFRASTRUCTURE_DEFINITIONS_HPP_

#include <cstdlib>
#include <SFML/System/Vector2.hpp>

namespace drl {

	using EntityId = std::size_t;

	class Definitions {
	public:
		Definitions(void) = delete;
		~Definitions(void) = delete;

		static constexpr const char OreResourceName[] = "Ore";
		static constexpr const char OreExchangeRateResourceName[] = "OreExchangeRate";
		static constexpr const char ResearchResourceName[] = "ResearchPoint";
		static constexpr const char MoneyResourceName[] = "Money";

		static constexpr const char CurrentWorkerResourceName[] = "CurrentWorker";

		static constexpr const char CurrentBuilderResourceName[] = "CurrentBuilder";
		static constexpr const char CurrentMinerResourceName[] = "CurrentMiner";
		static constexpr const char CurrentRefinerResourceName[] = "CurrentRefiner";
		static constexpr const char CurrentResearcherResourceName[] = "CurrentResearcher";

		static constexpr const char TileSpriteSheetTextureName[] = "tile_sprite_sheet";

		static constexpr const char BuildingBunkPrototypeName[] = "Building_Bunk";
		static constexpr const char BuildingBuilderPrototypeName[] = "Building_Builder";
		static constexpr const char BuildingMinerPrototypeName[] = "Building_Miner";
		static constexpr const char BuildingRefinerPrototypeName[] = "Building_Refining";
		static constexpr const char BuildingResearcherPrototypeName[] = "Building_Researcher";
		static constexpr const char BuildingRecreationPrototypeName[] = "Building_Recreation";
		static constexpr const char BuildingDiningPrototypeName[] = "Building_Dining";

		static constexpr const char JobPrototypeName_Dig[] = "Job_Dig";
		static constexpr const char JobPrototypeName_BuildBuilding[] = "Job_BuildBuilding";
		static constexpr const char JobPrototypeName_Miner[] = "Job_Miner";
		static constexpr const char JobPrototypeName_Refiner[] = "Job_Refiner";
		static constexpr const char JobPrototypeName_Researcher[] = "Job_Researcher";

		static constexpr const char WorkerPrototypeName_Builder[] = "Worker_Builder";
		static constexpr const char WorkerPrototypeName_Miner[] = "Worker_Miner";
		static constexpr const char WorkerPrototypeName_Refiner[] = "Worker_Refiner";
		static constexpr const char WorkerPrototypeName_Researcher[] = "Worker_Researcher";

		static constexpr const char ShuttlePrototypeName_Starting[] = "Shuttle_Starting";

		static constexpr const char ResearchCategory_WorkerMovementSpeed[] = "WorkerMovementSpeed";
		static constexpr const char ResearchCategory_WorkerWorkSpeed[] = "WorkerWorkSpeed";

		static constexpr const char NeedCategory_Sleep[] = "Sleep";
		static constexpr const char NeedCategory_Nutrition[] = "Nutrition";
		static constexpr const char NeedCategory_Fun[] = "Fun";
		
		static constexpr const float BaseNeedMax_Sleep{ 120.0f };
		static constexpr const float BaseNeedMax_Fun{ 80.0f };
		static constexpr const float BaseNeedMax_Nutrition{ 60.0f };

		static constexpr const float BaseNeed_Sleep{ BaseNeedMax_Sleep };
		static constexpr const float BaseNeed_Fun{ BaseNeedMax_Fun };
		static constexpr const float BaseNeed_Nutrition{ BaseNeedMax_Nutrition };

		static constexpr const float BaseNeedMin_Sleep{ 20.0f };
		static constexpr const float BaseNeedMin_Fun{ 16.0f };
		static constexpr const float BaseNeedMin_Nutrition{ 8.0f };

		static constexpr const float TileSize{ 1.0f };
		static constexpr const float GroundLevel{ -1.0f };
		static constexpr const float BaseShuttleSpeed{ 5.0f };
		static constexpr const float BaseWorkerMovementSpeed{ 2.0f };
		static constexpr const float BaseWorkerWorkSpeed{ 1.0f };
		static constexpr const float OreExchangeRateScale{ 1000.0f };

		static const sf::Vector2u BunkBuildingCoordinate;
		static const sf::Vector2u BuilderBuildingCoordinate;
		static const sf::Vector2u MinerBuildingCoordinate;
		static const sf::Vector2u RefinerBuildingCoordinate;
		static const sf::Vector2u ResearcherBuildingCoordinate;
		static const sf::Vector2u RecreationBuildingCoordinate;
		static const sf::Vector2u DiningBuildingCoordinate;

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