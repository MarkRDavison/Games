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
		sceneChange(_managerPackage.sceneManager),
		terrainAlteration(terrainData),
		buildingPrototype(identificationService),
		buildingPlacement(buildingData, terrainData, buildingPrototype),
		jobPrototype(identificationService),
		jobCreation(jobData, terrainAlteration, jobPrototype),
		jobAllocation(workerData, jobData, terrainAlteration),
		workerPrototype(identificationService),
		workerUpdate(workerData, jobData),
		gameCommand(resource, terrainAlteration, buildingPlacement, buildingPrototype, jobCreation, jobPrototype, jobAllocation, workerPrototype),
		game(gameCommand, jobAllocation, workerUpdate, terrainData, buildingData, jobData, workerData) {
		
	}

	drl::TerrainData terrainData;
	drl::BuildingData buildingData;
	drl::JobData jobData;
	drl::WorkerData workerData;
	drl::TerrainView terrainView;
	drl::BuildingView buildingView;
	drl::JobView jobView;
	drl::WorkerView workerView;
	inf::ResourceService resource;

	drl::SceneChangeService sceneChange;
	drl::TerrainAlterationService terrainAlteration;
	drl::BuildingPrototypeService buildingPrototype;
	drl::BuildingPlacementService buildingPlacement;
	drl::IdentificationService identificationService;
	drl::JobPrototypeService jobPrototype;
	drl::JobCreationService jobCreation;
	drl::JobAllocationService jobAllocation;
	drl::WorkerPrototypeService workerPrototype;
	drl::WorkerUpdateService workerUpdate;
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
			drl::GameScene *gameScene = new drl::GameScene(_managerPackage.config, _managerPackage.inputManager, _servicePackage.sceneChange, _servicePackage.gameCommand, _servicePackage.game, _servicePackage.terrainView, _servicePackage.buildingView, _servicePackage.jobView, _servicePackage.workerView);
			drl::GameUiScene *gameUiScene = new drl::GameUiScene(_servicePackage.sceneChange, _servicePackage.gameCommand);
			gameUiScene->setDeleteOnRemove(true);
			gameScene->setDeleteOnRemove(true);
			_sceneManager.pushScene(gameUiScene);
			_sceneManager.pushScene(gameScene);
		} else if (_currentState == drl::Definitions::GameSceneState::Exit) {
			drl::ExitScene *exitScene = new drl::ExitScene(_servicePackage.sceneChange);
			exitScene->setDeleteOnRemove(true);
			_sceneManager.pushScene(exitScene);
		}
	});

	_servicePackage.sceneChange.applicationClosed.registerCallback([&](void) {
		_managerPackage.app.stop();
	});
}

void registerPrototypes(ManagerPackage& _managerPackage, ServicePackage& _servicePackage) {
	_servicePackage.buildingPrototype.registerPrototype(drl::Definitions::Building1PrototypeName, drl::BuildingPrototype{ {1,1}, drl::Definitions::OneBuildingCoordinate   });
	_servicePackage.buildingPrototype.registerPrototype(drl::Definitions::Building2PrototypeName, drl::BuildingPrototype{ {2,1}, drl::Definitions::TwoBuildingCoordinate   });
	_servicePackage.buildingPrototype.registerPrototype(drl::Definitions::Building3PrototypeName, drl::BuildingPrototype{ {3,1}, drl::Definitions::ThreeBuildingCoordinate });
	_servicePackage.buildingPrototype.registerPrototype(drl::Definitions::Building4PrototypeName, drl::BuildingPrototype{ {4,1}, drl::Definitions::FourBuildingCoordinate  });
	_servicePackage.buildingPrototype.registerPrototype(drl::Definitions::Building5PrototypeName, drl::BuildingPrototype{ {5,1}, drl::Definitions::FiveBuildingCoordinate  });

	_servicePackage.jobPrototype.registerPrototype(drl::Definitions::JobPrototypeName_Dig, drl::JobPrototype{ });
	
	drl::WorkerPrototype allPrototype{ };
	allPrototype.validJobTypes = { inf::djb_hash(drl::Definitions::JobPrototypeName_Dig) };
	
	_servicePackage.workerPrototype.registerPrototype(drl::Definitions::WorkerPrototypeName_All, allPrototype);
}

void runSetupGameCommands(ManagerPackage& _managerPackage, ServicePackage& _servicePackage) {
	_servicePackage.gameCommand.executeGameCommand(drl::GameCommand(drl::GameCommand::DigShaftEvent{ 0 }));

	_servicePackage.gameCommand.executeGameCommand(drl::GameCommand(drl::GameCommand::DigTileEvent{ 0, +1 }));
	_servicePackage.gameCommand.executeGameCommand(drl::GameCommand(drl::GameCommand::DigTileEvent{ 0, -1 }));
	
	//_servicePackage.gameCommand.executeGameCommand(drl::GameCommand(drl::GameCommand::CreateJobEvent{ drl::Definitions::JobPrototypeName_Dig, {-2,0}, {1,1}, {} }));
	//_servicePackage.gameCommand.executeGameCommand(drl::GameCommand(drl::GameCommand::CreateJobEvent{ drl::Definitions::JobPrototypeName_Dig, {+2,0}, {1,1}, {} }));

	// TODO: These are created from prototypeService -> need an Id service of some sort
	drl::WorkerInstance& worker = _servicePackage.workerData.workers.emplace_back(_servicePackage.workerPrototype.createInstance(inf::djb_hash(drl::Definitions::WorkerPrototypeName_All)));
	worker.position = drl::Definitions::ShuttleLandingCoordinates;
}

int main(int _argc, char **_argv) {
	ManagerPackage managerPackage;
	ServicePackage servicePackage(managerPackage);

	managerPackage.config.loadConfiguration("./data/scripts/Driller/config.lua");

	managerPackage.app.initialise(managerPackage.config.getResolution(), managerPackage.config.getTitle(), managerPackage.config.getGameViewScale());
	managerPackage.inputManager.m_GetWindowSizeCallback = [&managerPackage]() { return sf::Vector2i(managerPackage.app.getWindow().getSize()); };
	managerPackage.inputManager.m_GetMousePositionCallback = [&managerPackage]() { return sf::Mouse::getPosition(managerPackage.app.getWindow()); };

	managerPackage.textureManager.loadTexture("./data/textures/Driller/tile_sprite_sheet.png", drl::Definitions::TileSpriteSheetTextureName);

	setupSceneTransitions(managerPackage, servicePackage);

	servicePackage.sceneChange.setSceneState(drl::Definitions::GameSceneState::Title);

	registerPrototypes(managerPackage, servicePackage);
	runSetupGameCommands(managerPackage, servicePackage);

	managerPackage.app.start();

	return EXIT_SUCCESS;
}
