#include <Infrastructure/FontManager.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/LuaManager.hpp>
#include <Infrastructure/SceneManager.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/Application.hpp>

#include <Infrastructure/Services/PathfindingService.hpp>

#include <EntityComponentSystem/EntityManager.hpp>
#include <Minesweeper/Infrastructure/ConfigurationManager.hpp>
#include <Minesweeper/Infrastructure/Definitions.hpp>
#include <Minesweeper/Scenes/TitleScene.hpp>
#include <Minesweeper/Services/SceneChangeService.hpp>
#include <Minesweeper/Scenes/ExitScene.hpp>
#include <Minesweeper/Scenes/GameScene.hpp>
#include <Minesweeper/Services/BoardInitializationService.hpp>
#include <Minesweeper/Services/BoardInteractionService.hpp>
#include <Minesweeper/Services/BoardStatusService.hpp>


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
	inf::PathfindingService pathfindingService;

	ecs::EntityManager entityManager;

	swp::ConfigurationManager config;
};

struct ServicePackage {
	
	ServicePackage(ManagerPackage& _managerPackage) :
		sceneChange(_managerPackage.sceneManager),
		boardInteraction(_managerPackage.inputManager, _managerPackage.config, boardInitialization, boardStatus) {
		
	}

	swp::SceneChangeService sceneChange;
	swp::BoardInitializationService boardInitialization;
	swp::BoardStatusService boardStatus;
	swp::BoardInteractionService boardInteraction;
};

int main(int _argc, char **_argv) {

	ManagerPackage managerPackage;
	ServicePackage servicePackage(managerPackage);

	managerPackage.luaManager.createState(swp::Definitions::GameLuaScope);
	managerPackage.config.loadConfiguration("./data/scripts/Minesweeper/config.lua");

	managerPackage.app.initialise(managerPackage.config.getResolution(), managerPackage.config.getTitle(), managerPackage.config.getGameViewScale()); 
	managerPackage.inputManager.m_GetWindowSizeCallback = [&managerPackage]() {
		return sf::Vector2i(managerPackage.app.getRenderTarget().getSize());
	};
	managerPackage.inputManager.m_GetMousePositionCallback = [&managerPackage]() {
		return sf::Mouse::getPosition(managerPackage.app.getWindow());
	};

	managerPackage.textureManager.loadTexture("./data/textures/Minesweeper/cell_spritesheet.png", swp::Definitions::CellSpriteSheetTextureName);
	managerPackage.textureManager.loadTexture("./data/textures/Minesweeper/face_sprite_sheet.png", swp::Definitions::FaceSpriteSheetTextureName);

	swp::TitleScene *titleScene = new swp::TitleScene(managerPackage.textureManager, managerPackage.fontManager, managerPackage.inputManager, servicePackage.sceneChange);
	swp::ExitScene *exitScene = new swp::ExitScene(managerPackage.fontManager, managerPackage.inputManager, servicePackage.sceneChange);

	servicePackage.sceneChange.setTitleScene(titleScene);
	servicePackage.sceneChange.setExitScene(exitScene);

	servicePackage.sceneChange.closeApplication = [&](void) {
		managerPackage.app.stop();
	};

	servicePackage.sceneChange.createGameScene = [&](void) {
		servicePackage.boardStatus.winSignal.clearCallbacks();
		servicePackage.boardStatus.loseSignal.clearCallbacks();

		const sf::Vector2u Size{ 22, 22 };
		const unsigned Mines{ 10 };
		servicePackage.boardStatus.initialize(Size, Mines);
		servicePackage.boardInteraction.setEnabled(true);

		swp::GameBoard *board = new swp::GameBoard(managerPackage.textureManager, servicePackage.boardInteraction);
		board->initialize(Size, Mines);
		board->initializeGraphics();

		swp::GameScene *scene = new swp::GameScene(managerPackage.textureManager, managerPackage.inputManager, managerPackage.config, servicePackage.sceneChange, servicePackage.boardStatus, servicePackage.boardInteraction);
		scene->setGameBoard(board);

		return scene;
	};

	managerPackage.sceneManager.pushScene(titleScene);

	managerPackage.app.start();

	return EXIT_SUCCESS;
}