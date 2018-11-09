#include <cstdlib>

#include <Infrastructure/Application.hpp>
#include <Infrastructure/SceneManager.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/LuaManager.hpp>
#include <Infrastructure/Services/ResourceService.hpp>

#include <Driller/Infrastructure/ConfigurationManager.hpp>

#include <Driller/Services/SceneChangeService.hpp>

#include <Driller/Core/Game.hpp>

#include <Driller/Scenes/ExitScene.hpp>
#include <Driller/Scenes/GameScene.hpp>
#include <Driller/Scenes/GameUiScene.hpp>
#include <Driller/Scenes/TitleScene.hpp>

#include <Driller/Services/GameCommandService.hpp>
#include <Driller/Services/TerrainAlterationService.hpp>
#include <Driller/Services/BuildingPlacementService.hpp>
#include <Driller/Services/BuildingPrototypeService.hpp>
#include <Driller/Services/JobPrototypeService.hpp>
#include <Driller/Services/WorkerPrototypeService.hpp>
#include <Driller/Services/JobCreationService.hpp>
#include <Driller/Services/JobAllocationService.hpp>
#include <Driller/Services/WorkerUpdateService.hpp>
#include <Driller/Services/IdentificationService.hpp>
#include <Driller/Services/WorkerCreationService.hpp>
#include <Driller/Services/JobCompletionService.hpp>
#include <Driller/Services/WorkerClassService.hpp>
#include <Driller/Services/ShuttlePrototypeService.hpp>
#include <Driller/Services/ShuttleCreationService.hpp>
#include <Driller/Services/ShuttleDepartureService.hpp>
#include <Driller/Services/ShuttleCompletionService.hpp>
#include <Driller/Services/MarketService.hpp>
#include <Driller/Services/ShuttleUpdateService.hpp>
#include <Driller/Services/WorkerRecruitmentService.hpp>
#include <Driller/Services/ShuttleCargoService.hpp>
#include <Driller/Services/CostService.hpp>
#include <Driller/Services/ResearchService.hpp>
#include <Driller/Services/NeedProviderLocationService.hpp>

struct ManagerPackage {

	ManagerPackage() :
		app(fontManager, sceneManager),
		config(luaManager) {
	}

	inf::FontManager fontManager;
	inf::SceneManager sceneManager;
	inf::TextureManager textureManager;
	inf::LuaManager luaManager;
	inf::InputManager inputManager;
	inf::Application app;

	drl::ConfigurationManager config;
};

struct ServicePackage {
	
	explicit ServicePackage(ManagerPackage& _managerPackage) :
		terrainView(_managerPackage.textureManager, terrainData),
		buildingView(_managerPackage.textureManager, buildingData),
		jobView(_managerPackage.textureManager, jobData),
		workerView(workerData),
		shuttleView(shuttleData),
		market(resource),
		sceneChange(_managerPackage.sceneManager),
		terrainAlteration(terrainData),
		buildingPrototype(identificationService),
		buildingPlacement(buildingData, terrainAlteration, buildingPrototype, workerClass, shuttleDeparture, resource),
		needProviderLocationService(buildingData),
		jobPrototype(identificationService),
		jobCreation(jobData, terrainAlteration, jobPrototype, buildingPlacement, buildingPrototype, cost, resource),
		jobAllocation(workerData, jobData, terrainAlteration),
		jobCompletion(jobData, terrainAlteration),
		workerClass(resource),
		workerCreation(workerData, workerPrototype, workerClass),
		workerPrototype(identificationService),
		workerUpdate(workerData, buildingData, jobData, jobCompletion, needProviderLocationService),
		workerRecruitment(workerCreation, shuttleDeparture),
		shuttlePrototype(identificationService),
		shuttleCreation(shuttleData, shuttlePrototype),
		shuttleDeparture(shuttleCreation),
		shuttleCompletion(shuttleData, market, shuttleDeparture),
		shuttleCargo(resource),
		shuttleUpdate(shuttleData, shuttleCompletion, shuttleCargo, workerRecruitment),
		research(researchData),
		gameCommand(resource, terrainAlteration, buildingPlacement, buildingPrototype, jobCreation, jobPrototype, jobAllocation, workerCreation, workerPrototype, shuttleCreation, cost, research),
		game(gameCommand, jobAllocation, jobCompletion, workerUpdate, shuttleDeparture, shuttleUpdate, shuttleCompletion, terrainData, buildingData, jobData, workerData) {
	}

	drl::TerrainData terrainData;
	drl::BuildingData buildingData;
	drl::JobData jobData;
	drl::WorkerData workerData;
	drl::ShuttleData shuttleData;
	drl::ResearchData researchData;
	drl::TerrainView terrainView;
	drl::BuildingView buildingView;
	drl::JobView jobView;
	drl::WorkerView workerView;
	drl::ShuttleView shuttleView;
	inf::ResourceService resource;

	drl::MarketService market;
	drl::SceneChangeService sceneChange;
	drl::TerrainAlterationService terrainAlteration;
	drl::BuildingPrototypeService buildingPrototype;
	drl::BuildingPlacementService buildingPlacement;
	drl::NeedProviderLocationService needProviderLocationService;
	drl::IdentificationService identificationService;
	drl::JobPrototypeService jobPrototype;
	drl::JobCreationService jobCreation;
	drl::JobAllocationService jobAllocation;
	drl::JobCompletionService jobCompletion;
	drl::WorkerClassService workerClass;
	drl::WorkerCreationService workerCreation;
	drl::WorkerPrototypeService workerPrototype;
	drl::WorkerUpdateService workerUpdate;
	drl::WorkerRecruitmentService workerRecruitment;
	drl::ShuttlePrototypeService shuttlePrototype;
	drl::ShuttleCreationService shuttleCreation;
	drl::ShuttleDepartureService shuttleDeparture;
	drl::ShuttleCompletionService shuttleCompletion;
	drl::ShuttleCargoService shuttleCargo;
	drl::ShuttleUpdateService shuttleUpdate;
	drl::CostService cost;
	drl::ResearchService research;
	drl::GameCommandService gameCommand;
	drl::Game game;
};

void setupSceneTransitions(ManagerPackage& _managerPackage, ServicePackage& _servicePackage) {
	_servicePackage.sceneChange.sceneStateChanged.registerCallback([&](inf::SceneManager& _sceneManager, drl::Definitions::GameSceneState _previousState, drl::Definitions::GameSceneState _currentState) {
		_sceneManager.clearScenes();

		if (_currentState == drl::Definitions::GameSceneState::Title) {
			drl::TitleScene *titleScene = new drl::TitleScene(_managerPackage.fontManager, _managerPackage.textureManager, _servicePackage.sceneChange);
			titleScene->setDeleteOnRemove(true);
			_sceneManager.pushScene(titleScene);
		} else if (_currentState == drl::Definitions::GameSceneState::Gameplay) {
			drl::GameScene *gameScene = new drl::GameScene(_managerPackage.config, _managerPackage.inputManager, _servicePackage.sceneChange, _servicePackage.gameCommand, _servicePackage.game, _servicePackage.terrainView, _servicePackage.buildingView, _servicePackage.jobView, _servicePackage.workerView, _servicePackage.shuttleView);
			drl::GameUiScene *gameUiScene = new drl::GameUiScene(_servicePackage.sceneChange, _managerPackage.fontManager, _servicePackage.resource, _servicePackage.gameCommand);
			gameScene->setDeleteOnRemove(true);
			gameUiScene->setDeleteOnRemove(true);
			_sceneManager.pushScene(gameScene);
			_sceneManager.pushScene(gameUiScene);
		} else if (_currentState == drl::Definitions::GameSceneState::Exit) {
			drl::ExitScene *exitScene = new drl::ExitScene(_servicePackage.sceneChange);
			exitScene->setDeleteOnRemove(true);
			_sceneManager.pushScene(exitScene);
		}
	});

	_servicePackage.sceneChange.applicationClosed.registerCallback([&](void) -> void {
		_managerPackage.app.stop();
	});
}

void registerPrototypes(ManagerPackage& _managerPackage, ServicePackage& _servicePackage) {
	{
		_servicePackage.workerClass.registerPrototypeToResourceClass(inf::djb_hash(drl::Definitions::WorkerPrototypeName_Builder),		drl::Definitions::CurrentBuilderResourceName);
		_servicePackage.workerClass.registerPrototypeToResourceClass(inf::djb_hash(drl::Definitions::WorkerPrototypeName_Miner),		drl::Definitions::CurrentMinerResourceName);
		_servicePackage.workerClass.registerPrototypeToResourceClass(inf::djb_hash(drl::Definitions::WorkerPrototypeName_Refiner),		drl::Definitions::CurrentRefinerResourceName);
		_servicePackage.workerClass.registerPrototypeToResourceClass(inf::djb_hash(drl::Definitions::WorkerPrototypeName_Researcher),	drl::Definitions::CurrentResearcherResourceName);
	}
	{
		drl::ShuttlePrototype startingShuttlePrototype{};
		startingShuttlePrototype.capacity = 25;
		startingShuttlePrototype.loadingTime = 5.0f;
		_servicePackage.shuttlePrototype.registerPrototype(drl::Definitions::ShuttlePrototypeName_Starting, startingShuttlePrototype);
		_servicePackage.shuttleDeparture.registerShuttle(inf::djb_hash(drl::Definitions::ShuttlePrototypeName_Starting), 10.0f);
	}
	{
		drl::WorkerPrototype builderPrototype{ };
		builderPrototype.validJobTypes = {
			inf::djb_hash(drl::Definitions::JobPrototypeName_Dig),
			inf::djb_hash(drl::Definitions::JobPrototypeName_BuildBuilding)
		};
		_servicePackage.workerPrototype.registerPrototype(drl::Definitions::WorkerPrototypeName_Builder, builderPrototype);
	}
	{
		drl::WorkerPrototype minerPrototype{ };
		minerPrototype.validJobTypes = {
			inf::djb_hash(drl::Definitions::JobPrototypeName_Miner)
		};
		_servicePackage.workerPrototype.registerPrototype(drl::Definitions::WorkerPrototypeName_Miner, minerPrototype);
	}
	{
		drl::WorkerPrototype refinerPrototype{ };
		refinerPrototype.validJobTypes = {
			inf::djb_hash(drl::Definitions::JobPrototypeName_Refiner)
		};
		_servicePackage.workerPrototype.registerPrototype(drl::Definitions::WorkerPrototypeName_Refiner, refinerPrototype);
	}
	{
		drl::WorkerPrototype researcherPrototype{ };
		researcherPrototype.validJobTypes = {
			inf::djb_hash(drl::Definitions::JobPrototypeName_Researcher)
		};
		_servicePackage.workerPrototype.registerPrototype(drl::Definitions::WorkerPrototypeName_Researcher, researcherPrototype);
	}
	{
		drl::BuildingPrototype bunkPrototype = drl::BuildingPrototype{ {2,1}, drl::Definitions::BunkBuildingCoordinate };
		bunkPrototype.cost.resources.emplace_back(drl::Definitions::MoneyResourceName, 60);
		bunkPrototype.providedNeedId = inf::djb_hash(drl::Definitions::NeedCategory_Sleep);
		bunkPrototype.providedNeedRate = 16.0f;
		bunkPrototype.providesNeeds = true;
		{
			drl::BuildingProvidedNeed& need = bunkPrototype.providedNeeds.emplace_back();
			need.offset = { 0.0f, 0.0f };
		}
		{
			drl::BuildingProvidedNeed& need = bunkPrototype.providedNeeds.emplace_back();
			need.offset = { 1.0f, 0.0f };
		}
		_servicePackage.buildingPrototype.registerPrototype(drl::Definitions::BuildingBunkPrototypeName, bunkPrototype);
	}
	{
		drl::BuildingPrototype recreationPrototype = drl::BuildingPrototype{ {3,1}, drl::Definitions::RecreationBuildingCoordinate };
		recreationPrototype.cost.resources.emplace_back(drl::Definitions::MoneyResourceName, 60);
		recreationPrototype.providedNeedId = inf::djb_hash(drl::Definitions::NeedCategory_Fun);
		recreationPrototype.providedNeedRate = 32.0f;
		recreationPrototype.providesNeeds = true;
		{
			drl::BuildingProvidedNeed& need = recreationPrototype.providedNeeds.emplace_back();
			need.offset = { 0.0f, 0.0f };
		}
		{
			drl::BuildingProvidedNeed& need = recreationPrototype.providedNeeds.emplace_back();
			need.offset = { 1.0f, 0.0f };
		}
		{
			drl::BuildingProvidedNeed& need = recreationPrototype.providedNeeds.emplace_back();
			need.offset = { 2.0f, 0.0f };
		}
		_servicePackage.buildingPrototype.registerPrototype(drl::Definitions::BuildingRecreationPrototypeName, recreationPrototype);
	}
	{
		drl::BuildingPrototype diningPrototype = drl::BuildingPrototype{ {3,1}, drl::Definitions::DiningBuildingCoordinate };
		diningPrototype.cost.resources.emplace_back(drl::Definitions::MoneyResourceName, 60);
		diningPrototype.providedNeedId = inf::djb_hash(drl::Definitions::NeedCategory_Nutrition);
		diningPrototype.providedNeedRate = 24.0f;
		diningPrototype.providesNeeds = true;
		{
			drl::BuildingProvidedNeed& need = diningPrototype.providedNeeds.emplace_back();
			need.offset = { 0.0f, 0.0f };
		}
		{
			drl::BuildingProvidedNeed& need = diningPrototype.providedNeeds.emplace_back();
			need.offset = { 1.0f, 0.0f };
		}
		{
			drl::BuildingProvidedNeed& need = diningPrototype.providedNeeds.emplace_back();
			need.offset = { 2.0f, 0.0f };
		}
		_servicePackage.buildingPrototype.registerPrototype(drl::Definitions::BuildingDiningPrototypeName, diningPrototype);
	}
	{
		drl::BuildingPrototype builderPrototype = drl::BuildingPrototype{ {2,1}, drl::Definitions::BuilderBuildingCoordinate };
		builderPrototype.providedWorkerPrototypeId = inf::djb_hash(drl::Definitions::WorkerPrototypeName_Builder);
		builderPrototype.providedWorkerPrototypeAmount = 1;
		builderPrototype.cost.resources.emplace_back(drl::Definitions::MoneyResourceName, 80);
		_servicePackage.buildingPrototype.registerPrototype(drl::Definitions::BuildingBuilderPrototypeName, builderPrototype);
	}
	{
		drl::BuildingPrototype minerPrototype = drl::BuildingPrototype{ {3,1}, drl::Definitions::MinerBuildingCoordinate };
		minerPrototype.providedWorkerPrototypeId = inf::djb_hash(drl::Definitions::WorkerPrototypeName_Miner);
		minerPrototype.cost.resources.emplace_back(drl::Definitions::MoneyResourceName, 40);
		{
			drl::BuildingProvidedJob& job = minerPrototype.providedJobs.emplace_back();
			job.location = { 1,0 };
			job.prototypeId = inf::djb_hash(drl::Definitions::JobPrototypeName_Miner);
		}
		minerPrototype.providedWorkerPrototypeAmount = minerPrototype.providedJobs.size();
		minerPrototype.providesJobs = !minerPrototype.providedJobs.empty();
		_servicePackage.buildingPrototype.registerPrototype(drl::Definitions::BuildingMinerPrototypeName, minerPrototype);
	}
	{
		drl::BuildingPrototype refinerPrototype = drl::BuildingPrototype{ {4,1}, drl::Definitions::RefinerBuildingCoordinate };
		refinerPrototype.providedWorkerPrototypeId = inf::djb_hash(drl::Definitions::WorkerPrototypeName_Refiner);
		refinerPrototype.cost.resources.emplace_back(drl::Definitions::MoneyResourceName, 100); 
		{
			drl::BuildingProvidedJob& job = refinerPrototype.providedJobs.emplace_back();
			job.location = { 1,0 };
			job.prototypeId = inf::djb_hash(drl::Definitions::JobPrototypeName_Refiner);
		} 
		{
			drl::BuildingProvidedJob& job = refinerPrototype.providedJobs.emplace_back();
			job.location = { 2,0 };
			job.prototypeId = inf::djb_hash(drl::Definitions::JobPrototypeName_Refiner);
		}
		refinerPrototype.providedWorkerPrototypeAmount = refinerPrototype.providedJobs.size();
		refinerPrototype.providesJobs = !refinerPrototype.providedJobs.empty();
		_servicePackage.buildingPrototype.registerPrototype(drl::Definitions::BuildingRefinerPrototypeName, refinerPrototype);
	}
	{
		drl::BuildingPrototype researcherPrototype = drl::BuildingPrototype{ {5,1}, drl::Definitions::ResearcherBuildingCoordinate };
		researcherPrototype.providedWorkerPrototypeId = inf::djb_hash(drl::Definitions::WorkerPrototypeName_Researcher);
		researcherPrototype.cost.resources.emplace_back(drl::Definitions::MoneyResourceName, 200);
		{
			drl::BuildingProvidedJob& job = researcherPrototype.providedJobs.emplace_back();
			job.location = { 0,0 };
			job.prototypeId = inf::djb_hash(drl::Definitions::JobPrototypeName_Researcher);
		}
		{
			drl::BuildingProvidedJob& job = researcherPrototype.providedJobs.emplace_back();
			job.location = { 2,0 };
			job.prototypeId = inf::djb_hash(drl::Definitions::JobPrototypeName_Researcher);
		}
		{
			drl::BuildingProvidedJob& job = researcherPrototype.providedJobs.emplace_back();
			job.location = { 4,0 };
			job.prototypeId = inf::djb_hash(drl::Definitions::JobPrototypeName_Researcher);
		}
		researcherPrototype.providedWorkerPrototypeAmount = researcherPrototype.providedJobs.size();
		researcherPrototype.providesJobs = !researcherPrototype.providedJobs.empty();
		_servicePackage.buildingPrototype.registerPrototype(drl::Definitions::BuildingResearcherPrototypeName, researcherPrototype);
	}
	{
		drl::JobPrototype digDirtProtoype{};
		digDirtProtoype.workRequired = 2.0f;
		_servicePackage.jobPrototype.registerPrototype(drl::Definitions::JobPrototypeName_Dig, digDirtProtoype);

		drl::JobCompleteDelegate digDirtCompletePrototype = [&](const drl::JobInstance& _jobInstance) {
			_servicePackage.gameCommand.executeGameCommand(drl::GameCommand(drl::GameCommand::DigTileEvent{ _jobInstance.coordinates.y, _jobInstance.coordinates.x }));
		};
		_servicePackage.jobCompletion.registerJobCompleteDelegate(drl::Definitions::JobPrototypeName_Dig, digDirtCompletePrototype);
	}
	{
		drl::JobPrototype buildBuildingPrototype{};
		buildBuildingPrototype.workRequired = 2.0f;
		_servicePackage.jobPrototype.registerPrototype(drl::Definitions::JobPrototypeName_BuildBuilding, buildBuildingPrototype);

		drl::JobCompleteDelegate buildBuildingCompletePrototype = [&](const drl::JobInstance& _jobInstance) -> void {
			drl::GameCommand::PlaceBuildingEvent event{};
			event.prototypeId = _jobInstance.additionalPrototypeId;
			event.level = _jobInstance.coordinates.y;
			event.column = _jobInstance.coordinates.x;
			_servicePackage.gameCommand.executeGameCommand(drl::GameCommand{ event });
		};
		_servicePackage.jobCompletion.registerJobCompleteDelegate(drl::Definitions::JobPrototypeName_BuildBuilding, buildBuildingCompletePrototype);
	}
	{
		drl::JobPrototype minePrototype{}; 
		minePrototype.workRequired = 2.0f;
		minePrototype.repeats = true;
		_servicePackage.jobPrototype.registerPrototype(drl::Definitions::JobPrototypeName_Miner, minePrototype);
		
		drl::JobCompleteDelegate mineCompletePrototype = [&](const drl::JobInstance& _jobInstance) -> void {
			inf::ResourceBundle bundle{};
			bundle.resources.emplace_back(drl::Definitions::OreResourceName, _jobInstance.coordinates.y + 1);
			_servicePackage.resource.receiveResourceBundle(bundle);
		};
		_servicePackage.jobCompletion.registerJobCompleteDelegate(drl::Definitions::JobPrototypeName_Miner, mineCompletePrototype);
	}
	{
		drl::JobPrototype refinePrototype{};
		refinePrototype.workRequired = 12.0f;
		refinePrototype.repeats = true;
		_servicePackage.jobPrototype.registerPrototype(drl::Definitions::JobPrototypeName_Refiner, refinePrototype);

		drl::JobCompleteDelegate refineCompletePrototype = [&](const drl::JobInstance& _jobInstance) -> void {
			inf::ResourceBundle bundle{};
			bundle.resources.emplace_back(drl::Definitions::OreExchangeRateResourceName, _jobInstance.coordinates.y + 1);
			_servicePackage.resource.receiveResourceBundle(bundle);
		};
		_servicePackage.jobCompletion.registerJobCompleteDelegate(drl::Definitions::JobPrototypeName_Refiner, refineCompletePrototype);
	}
	{
		drl::JobPrototype researchPrototype{};
		researchPrototype.workRequired = 12.0f;
		researchPrototype.repeats = true;
		_servicePackage.jobPrototype.registerPrototype(drl::Definitions::JobPrototypeName_Researcher, researchPrototype);

		drl::JobCompleteDelegate researchCompletePrototype = [&](const drl::JobInstance& _jobInstance) -> void {
			inf::ResourceBundle bundle{};
			bundle.resources.emplace_back(drl::Definitions::ResearchResourceName, _jobInstance.coordinates.y + 1);
			_servicePackage.resource.receiveResourceBundle(bundle);
		};
		_servicePackage.jobCompletion.registerJobCompleteDelegate(drl::Definitions::JobPrototypeName_Researcher, researchCompletePrototype);
	}
}

void initialiseResources(ManagerPackage& _managerPackage, ServicePackage& _servicePackage) {
	_servicePackage.resource.setResource(drl::Definitions::MoneyResourceName, 2000);
	_servicePackage.resource.setResource(drl::Definitions::OreResourceName, 0);
	_servicePackage.resource.setResource(drl::Definitions::OreExchangeRateResourceName, 0);
	_servicePackage.resource.setResource(drl::Definitions::ResearchResourceName, 0);
	_servicePackage.resource.setResource(drl::Definitions::CurrentBuilderResourceName, 0);
	_servicePackage.resource.setResourceMaximum(drl::Definitions::CurrentBuilderResourceName, 0);
	_servicePackage.resource.setResource(drl::Definitions::CurrentMinerResourceName, 0);
	_servicePackage.resource.setResourceMaximum(drl::Definitions::CurrentMinerResourceName, 0);
	_servicePackage.resource.setResource(drl::Definitions::CurrentRefinerResourceName, 0);
	_servicePackage.resource.setResourceMaximum(drl::Definitions::CurrentRefinerResourceName, 0);
	_servicePackage.resource.setResource(drl::Definitions::CurrentResearcherResourceName, 0);
	_servicePackage.resource.setResourceMaximum(drl::Definitions::CurrentResearcherResourceName, 0);
}

void runSetupGameCommands(ManagerPackage& _managerPackage, ServicePackage& _servicePackage) {
	_servicePackage.gameCommand.executeGameCommand(drl::GameCommand(drl::GameCommand::DigShaftEvent{ 0 }));
	_servicePackage.gameCommand.executeGameCommand(drl::GameCommand(drl::GameCommand::DigTileEvent{ 0, +1 }));
	_servicePackage.gameCommand.executeGameCommand(drl::GameCommand(drl::GameCommand::DigTileEvent{ 0, +2 }));
	_servicePackage.gameCommand.executeGameCommand(drl::GameCommand(drl::GameCommand::PlaceBuildingEvent{ drl::Definitions::BuildingBuilderPrototypeName, 0, +1 }));
}

void initialiseResearch(ManagerPackage& _managerPackage, ServicePackage& _servicePackage) {
	{
		_servicePackage.research.registerResearchCategory(drl::Definitions::ResearchCategory_WorkerMovementSpeed);

		for (unsigned i = 1; i <= 10; ++i) {
			drl::ResearchInstance ri{};
			ri.cost.resources.emplace_back(drl::Definitions::ResearchResourceName, 50 + 50 * i * i * i * i * i);
			ri.level = i;
			ri.callback = [&](std::size_t _id, unsigned _level) -> void {
				_servicePackage.workerData.workerMovementSpeed *= 1.1f;
			};
			_servicePackage.research.registerResearchInstance(drl::Definitions::ResearchCategory_WorkerMovementSpeed, ri);
		}
	}
	{
		_servicePackage.research.registerResearchCategory(drl::Definitions::ResearchCategory_WorkerWorkSpeed);

		for (unsigned i = 1; i <= 10; ++i) {
			drl::ResearchInstance ri{};
			ri.cost.resources.emplace_back(drl::Definitions::ResearchResourceName, 50 + 50 * i * i * i * i * i);
			ri.level = i;
			ri.callback = [&](std::size_t _id, unsigned _level) -> void {
				_servicePackage.workerData.workerWorkSpeed *= 1.1f;
			};
			_servicePackage.research.registerResearchInstance(drl::Definitions::ResearchCategory_WorkerWorkSpeed, ri);
		}
	}
}

int main(int _argc, char **_argv) {
	ManagerPackage managerPackage;
	ServicePackage servicePackage(managerPackage);

	managerPackage.config.loadConfiguration("./data/scripts/Driller/config.lua");

	managerPackage.app.initialise(managerPackage.config.getResolution(), managerPackage.config.getTitle(), managerPackage.config.getGameViewScale());
	managerPackage.inputManager.m_GetWindowSizeCallback = [&managerPackage](void) -> sf::Vector2i { return sf::Vector2i(managerPackage.app.getWindow().getSize()); };
	managerPackage.inputManager.m_GetMousePositionCallback = [&managerPackage](void) -> sf::Vector2i { return sf::Mouse::getPosition(managerPackage.app.getWindow()); };
	managerPackage.inputManager.m_MapPixelToCoordsCallback = [&managerPackage](const sf::Vector2i& _pixel, const sf::View& _view) ->sf::Vector2f {return managerPackage.app.m_Window.mapPixelToCoords(_pixel, _view); };

	managerPackage.textureManager.loadTexture("./data/textures/Driller/tile_sprite_sheet.png", drl::Definitions::TileSpriteSheetTextureName);

	setupSceneTransitions(managerPackage, servicePackage);
	registerPrototypes(managerPackage, servicePackage);
	initialiseResources(managerPackage, servicePackage);
	initialiseResearch(managerPackage, servicePackage);
	runSetupGameCommands(managerPackage, servicePackage);

	servicePackage.sceneChange.setSceneState(drl::Definitions::GameSceneState::Gameplay);

	managerPackage.app.start();

	return EXIT_SUCCESS;
}
