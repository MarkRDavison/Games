#include <cstdlib>
#include <Infrastructure/Application.hpp>
#include <Infrastructure/SceneManager.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/LuaManager.hpp>

#include <Sovereign/Infrastructure/ConfigurationManager.hpp>

#include <Sovereign/Services/SceneChangeService.hpp>

#include <Sovereign/Core/Game.hpp>

#include <Sovereign/Scenes/ExitScene.hpp>
#include <Sovereign/Scenes/GameScene.hpp>
#include <Sovereign/Scenes/GameUiScene.hpp>
#include <Sovereign/Scenes/TitleScene.hpp>
#include <Sovereign/Services/LevelDataQueryService.hpp>
#include <Sovereign/Services/CollisionDetectionService.hpp>
#include <Sovereign/Services/CollisionResponseService.hpp>
#include <Sovereign/Services/LogService.hpp>

#include <Mocks/Sovereign/Services/LevelDataMutationServiceMock.hpp>
#include <Sovereign/Services/EntityMovementService.hpp>
#include <Sovereign/Services/PlayerControlService.hpp>
#include <Sovereign/Services/EntityDataQueryService.hpp>
#include <Sovereign/Services/EntityDataMutationService.hpp>

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

	sov::ConfigurationManager config;
};

struct ServicePackage {

	explicit ServicePackage(ManagerPackage& _managerPackage) :
		levelDataQueryService(levelData),
		collisionDetectionService(levelData, levelDataMutationService, levelDataQueryService),
		entityDataMutationService(entityData),
		entityDataQueryService(entityData),
		entityMovementService(entityData, collisionDetectionService, collisionResponseService),
		playerControlService(entityData, controlBindings),
		sceneChange(_managerPackage.sceneManager),
		game(levelData, entityData, controlBindings, logService, levelDataQueryService, levelDataMutationService, collisionDetectionService, collisionResponseService, entityDataQueryService, entityDataMutationService, entityMovementService, playerControlService) {
	}

	sov::LevelData levelData;
	sov::EntityData entityData;
	sov::ControlBindings controlBindings;

	sov::LogService logService;
	sov::LevelDataQueryService levelDataQueryService;
	sov::LevelDataMutationServiceMock levelDataMutationService;
	sov::CollisionDetectionService collisionDetectionService;
	sov::CollisionResponseService collisionResponseService;
	sov::EntityDataMutationService entityDataMutationService;
	sov::EntityDataQueryService entityDataQueryService;
	sov::EntityMovementService entityMovementService;
	sov::PlayerControlService playerControlService;

	sov::SceneChangeService sceneChange;
	sov::Game game;
};

void setupSceneTransitions(ManagerPackage& _managerPackage, ServicePackage& _servicePackage) {
	_servicePackage.sceneChange.sceneStateChanged.registerCallback([&](inf::SceneManager& _sceneManager, sov::Definitions::GameSceneState _previousState, sov::Definitions::GameSceneState _currentState) {
		_sceneManager.clearScenes(); 
		
		if (_currentState == sov::Definitions::GameSceneState::Title) {
			sov::TitleScene *titleScene = new sov::TitleScene(_managerPackage.fontManager, _servicePackage.sceneChange);
			titleScene->setDeleteOnRemove(true);
			_sceneManager.pushScene(titleScene);
		}
		else if (_currentState == sov::Definitions::GameSceneState::Gameplay) {
			sov::GameScene *gameScene = new sov::GameScene(_managerPackage.config, _managerPackage.inputManager, _managerPackage.textureManager, _servicePackage.logService, _servicePackage.sceneChange, _servicePackage.game);
			sov::GameUiScene *gameUiScene = new sov::GameUiScene(_servicePackage.sceneChange, _managerPackage.fontManager);

			gameScene->setDeleteOnRemove(true);
			gameUiScene->setDeleteOnRemove(true);

			_servicePackage.logService.onLog.clearCallbacks();
			_servicePackage.logService.onLog.registerCallback(std::bind(&sov::GameUiScene::log, gameUiScene, std::placeholders::_1, std::placeholders::_2));

			_sceneManager.pushScene(gameScene);
			_sceneManager.pushScene(gameUiScene);
		}
		else if (_currentState == sov::Definitions::GameSceneState::Exit) {
			sov::ExitScene *exitScene = new sov::ExitScene(_servicePackage.sceneChange);
			exitScene->setDeleteOnRemove(true);
			_sceneManager.pushScene(exitScene);
		}

	});

	_servicePackage.sceneChange.applicationClosed.registerCallback([&](void) {
		_managerPackage.app.stop();
	});
}

int main(int _argc, char **_argv) {
	ManagerPackage managerPackage;
	ServicePackage servicePackage(managerPackage);

	managerPackage.config.loadConfiguration("./data/scripts/Sovereign/config.lua");

	managerPackage.app.initialise(managerPackage.config.getResolution(), managerPackage.config.getTitle(), managerPackage.config.getGameViewScale());
	managerPackage.inputManager.m_GetWindowSizeCallback = [&managerPackage](void) -> sf::Vector2i { return sf::Vector2i(managerPackage.app.getWindow().getSize()); };
	managerPackage.inputManager.m_GetMousePositionCallback = [&managerPackage](void) -> sf::Vector2i { return sf::Mouse::getPosition(managerPackage.app.getWindow()); };
	managerPackage.inputManager.m_MapPixelToCoordsCallback = [&managerPackage](const sf::Vector2i& _pixel, const sf::View& _view) ->sf::Vector2f {return managerPackage.app.m_Window.mapPixelToCoords(_pixel, _view); };

	managerPackage.fontManager.loadFont("C:/Windows/Fonts/arial.ttf", sov::Definitions::DefaultFontName);
	managerPackage.textureManager.loadTexture("./data/textures/Sovereign/terrain.png", sov::Definitions::TerrainTextureName);

	setupSceneTransitions(managerPackage, servicePackage);

	const int Size = 2;

	for (int cy = 0; cy < Size; ++cy) {
		for (int cx = 0; cx < Size; ++cx) {
			sov::LevelChunk& lc = servicePackage.levelData.levelChunks.emplace_back();
			lc.x = cx;
			lc.y = cy;

			for (unsigned y = 0; y < sov::Definitions::ChunkSize; ++y) {
				for (unsigned x = 0; x < sov::Definitions::ChunkSize; ++x) {
					sov::LevelChunkCell& cell = lc.cells.emplace_back();
					cell.empty = true;
					if (cx == 0 && x == 0) {
						cell.empty = false;
					}
					if (cy == 0 && y == 0) {
						cell.empty = false;
					}
					if (cx == Size - 1 && x == sov::Definitions::ChunkSize - 1) {
						cell.empty = false;
					}
					if (cy == Size - 1 && y == sov::Definitions::ChunkSize - 1) {
						cell.empty = false;
					}

					if (cell.empty) {
						if (rand() % 7 == 0) {
							cell.empty = false;
						}
					}
				}
			}
		}
	}

	sov::EntityId id{0u};

	{ // Add player
		sov::MoveableEntity& me = servicePackage.entityData.moveableEntities.emplace_back();
		me.isPlayer = true;
		me.position = { 2.0f, 2.0f };
		me.size = { sov::Definitions::TileSize * 0.75f , sov::Definitions::TileSize * 0.75f };
		me.id = id++;
		servicePackage.entityData.playerId = me.id;
	}

	{ // Add random entities
		unsigned i = 0;
		while (i < 10) {
			const unsigned x = rand() % (sov::Definitions::ChunkSize * Size);
			const unsigned y = rand() % (sov::Definitions::ChunkSize * Size);

			if (servicePackage.levelDataQueryService.getLevelChunkCellForLevelChunk(x / sov::Definitions::ChunkSize, y / sov::Definitions::ChunkSize, x % sov::Definitions::ChunkSize, y % sov::Definitions::ChunkSize).empty) {
				sov::MoveableEntity& me = servicePackage.entityData.moveableEntities.emplace_back();
				me.position = { static_cast<float>(x) + 0.5f, static_cast<float>(y) + 0.5f };
				me.size = { sov::Definitions::TileSize * 0.75f , sov::Definitions::TileSize * 0.75f };
				me.id = id++;
				me.isPickup = rand() % 2 == 1;
				if (!me.isPickup) {
					me.isMineable = rand() % 2 == 1;
				}
				i++;
			}
		}
	}

	servicePackage.sceneChange.setSceneState(sov::Definitions::GameSceneState::Gameplay);

	managerPackage.app.start();

	return EXIT_SUCCESS;
}