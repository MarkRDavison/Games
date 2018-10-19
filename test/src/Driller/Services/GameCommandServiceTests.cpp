#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/GameCommandService.hpp>
#include <Driller/Scenes/GameScene.hpp>
#include <Mocks/Infrastructure/Services/ResourceServiceMock.hpp>
#include <Mocks/Driller/Services/TerrainAlterationServiceMock.hpp>
#include <Mocks/Driller/Services/BuildingPlacementServiceMock.hpp>
#include <Mocks/Driller/Services/PrototypeServiceMock.hpp>
#include <Mocks/Driller/Services/JobCreationServiceMock.hpp>
#include <Mocks/Driller/Services/JobAllocationServiceMock.hpp>
#include <Mocks/Driller/Services/WorkerCreationServiceMock.hpp>
#include <Mocks/Driller/Services/ShuttleCreationServiceMock.hpp>
#include <Mocks/Driller/Services/CostServiceMock.hpp>

namespace drl {
	namespace GameCommandServiceTests {
		
		struct GameCommandServicePackage {

			GameCommandServicePackage() : GameCommandServicePackage(0ll) {}
			GameCommandServicePackage(long long _startTick) :
				service(resourceService, terrainAlterationService, buildingPlacementService, buildingPrototypeService, jobCreationService, jobPrototypeServiceMock, jobAllocationServiceMock, workerCreationServiceMock, workerPrototypeServiceMock, shuttleCreationServiceMock, costServiceMock, _startTick) {

			}
			
			inf::ResourceServiceMock resourceService;
			TerrainAlterationServiceMock terrainAlterationService;
			BuildingPlacementServiceMock buildingPlacementService;
			BuildingPrototypeServiceMock buildingPrototypeService;
			JobCreationServiceMock jobCreationService;
			JobPrototypeServiceMock jobPrototypeServiceMock;
			JobAllocationServiceMock jobAllocationServiceMock;
			WorkerCreationServiceMock workerCreationServiceMock;
			WorkerPrototypeServiceMock workerPrototypeServiceMock;
			ShuttleCreationServiceMock shuttleCreationServiceMock;
			CostServiceMock costServiceMock;
			GameCommandService service;
		};

		TEST_CASE("Default constructor creates service with starting tick of zero", "[Driller][Services][GameCommandService]") {
			GameCommandServicePackage package;

			REQUIRE(0ll == package.service.getCurrentTick());
		}

		TEST_CASE("Constructor creates service with starting tick as given", "[Driller][Services][GameCommandService]") {
			const long long StartTick = 65123ll;
			GameCommandServicePackage package(StartTick);


			REQUIRE(StartTick == package.service.getCurrentTick());
		}

		TEST_CASE("Tick increases the current tick by 1", "[Driller][Services][GameCommandService]") {
			GameCommandServicePackage package;

			package.service.tick();
			REQUIRE(1ll == package.service.getCurrentTick());

			package.service.tick();
			REQUIRE(2ll == package.service.getCurrentTick());
		}

		TEST_CASE("execute game command looks at the resource service to determine if it can execute it", "[Driller][Services][GameCommandService]") {
			GameCommandServicePackage package;

			const GameCommand::AdjustResourceEvent adjustResource{ Definitions::MoneyResourceName , 5};
			const GameCommand command(adjustResource);

			bool canAffordInvoked = false;
			package.resourceService.canAffordIdCallback = [&](std::size_t _resourceId, int _amount) {
				canAffordInvoked = true;
				return false;
			};

			REQUIRE_FALSE(package.service.executeGameCommand(command));
			REQUIRE(canAffordInvoked);
		}

		TEST_CASE("execute game command pays resource by id if it can afford it", "[Driller][Services][GameCommandService]") {
			const char *ResourceName = Definitions::MoneyResourceName;
			const int ResourceAmount = 5;
			GameCommandServicePackage package;

			const GameCommand::AdjustResourceEvent adjustResource{ ResourceName , ResourceAmount };
			const GameCommand command(adjustResource);

			bool payResourceIdInvoked = false;
			package.resourceService.canAffordIdCallback = [&](std::size_t, int) { return true; };
			package.resourceService.payResourceIdCallback = [&](std::size_t _resourceId, int _amount) {
				REQUIRE(_resourceId == command.adjustResource.resourceId);
				REQUIRE(_amount == ResourceAmount);
				payResourceIdInvoked = true;
			};

			REQUIRE(package.service.executeGameCommand(command));
			REQUIRE(payResourceIdInvoked);
		}

		TEST_CASE("execute game command dig shaft passes information to the terrain alteration service as expected", "[Driller][Services][GameCommandService]") {
			const int Level{ 55 };
			GameCommandServicePackage package;
			
			const GameCommand::DigShaftEvent digShaft{ Level };
			const GameCommand command(digShaft);

			bool digShaftInvoked = false;
			package.terrainAlterationService.digShaftCallback = [&](int _level) {
				REQUIRE(Level == _level);
				digShaftInvoked = true;
				return false;
			};

			package.service.executeGameCommand(command);

			REQUIRE(digShaftInvoked);
		}

	} 
}
