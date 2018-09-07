#include <cstdlib>
#include <thread>

#include <Infrastructure/FontManager.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/LuaManager.hpp>
#include <Infrastructure/SceneManager.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/Application.hpp>
#include <Infrastructure/SplashScreen.hpp>

#include <Infrastructure/Services/PathfindingService.hpp>

#include <EntityComponentSystem/EntityManager.hpp>

#include <Intrusion/Infrastructure/IntrusionConfigurationManager.hpp>
#include <Intrusion/Infrastructure/IntrusionDefinitions.hpp>
#include <Intrusion/Infrastructure/LuaLevelParser.hpp>
#include <Intrusion/Scenes/StartScene.hpp>
#include <Intrusion/Scenes/GameScene.hpp>
#include <Intrusion/Scenes/GameUiScene.hpp>
#include <Intrusion/Infrastructure/EntityFactory.hpp>
#include <Intrusion/Infrastructure/LuaEntityParser.hpp>
#include <Intrusion/Systems/PathFollowingSystem.hpp>

#define ARTIFICIAL_WAIT 150

struct ManagerPackage {

	ManagerPackage() :
		app(fontManager, sceneManager),
		config(luaManager),
		luaEntityParser(luaManager),
		luaLevelParser(luaManager),
		entityFactory(textureManager, entityManager, config, luaEntityParser) {
	}

	inf::FontManager fontManager;
	inf::SceneManager sceneManager;
	inf::TextureManager textureManager;
	inf::LuaManager luaManager;
	inf::InputManager inputManager;
	inf::Application app;
	inf::PathfindingService pathfindingService;

	ecs::EntityManager entityManager; 

	itr::IntrusionConfigurationManager config;
	itr::LuaEntityParser luaEntityParser;
	itr::LuaLevelParser luaLevelParser;
	itr::EntityFactory entityFactory;
};

struct SystemPackage {
	itr::RenderSystem render;
	itr::PathFollowingSystem pathFollowing;
};

void loadResources(inf::SplashScreen& _splashScreen, ManagerPackage& _managerPackage, SystemPackage& _systemPackage) {
	{
		_splashScreen.setLoadingState(0, "Loading configuration");
		_managerPackage.luaManager.createState(itr::Definitions::EntityParseLuaStateScope);
		_managerPackage.luaManager.createState(itr::Definitions::LevelParseLuaStateScope);
		_managerPackage.config.loadConfiguration("./data/scripts/Intrusion/config.lua");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		_splashScreen.setLoadingState(10, "Loading textures");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
		_splashScreen.setLoadingState(11, "Loading texture 'terrain'");
		_managerPackage.textureManager.loadTexture("./data/textures/Intrusion/terrain.png", itr::Definitions::TerrainTextureName);
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
		_splashScreen.setLoadingState(12, "Loading texture 'spear_icon'");
		_managerPackage.textureManager.loadTexture("./data/textures/Intrusion/spear_icon.png", itr::Definitions::SpearIconTextureName);
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
		_splashScreen.setLoadingState(13, "Loading texture 'missing'");
		_managerPackage.textureManager.loadTexture("./data/textures/Intrusion/missing.png", itr::Definitions::MissingTextureName);
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		_splashScreen.setLoadingState(20, "Loading fonts");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		_splashScreen.setLoadingState(30, "Loading sound effects");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		_splashScreen.setLoadingState(40, "Loading music");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		_splashScreen.setLoadingState(50, "Loading levels");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
		_splashScreen.setLoadingState(51, "Loading level1");
		_managerPackage.luaLevelParser.parseLevel("./data/scripts/Intrusion/Levels/Level1.lua");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
		_splashScreen.setLoadingState(52, "Loading level2");
		_managerPackage.luaLevelParser.parseLevel("./data/scripts/Intrusion/Levels/Level2.lua");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
		_splashScreen.setLoadingState(53, "Loading level3");
		_managerPackage.luaLevelParser.parseLevel("./data/scripts/Intrusion/Levels/Level3.lua");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
		_splashScreen.setLoadingState(54, "Loading level4");
		_managerPackage.luaLevelParser.parseLevel("./data/scripts/Intrusion/Levels/Level4.lua");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		_splashScreen.setLoadingState(60, "Loading tower prototypes");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		_splashScreen.setLoadingState(70, "Loading entity prototypes");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
		_splashScreen.setLoadingState(71, "Loading entity1");
		_managerPackage.luaEntityParser.parseEntity("./data/scripts/Intrusion/Entities/Entity1.lua");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
		_splashScreen.setLoadingState(72, "Loading entity2");
		_managerPackage.luaEntityParser.parseEntity("./data/scripts/Intrusion/Entities/Entity2.lua");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
		_splashScreen.setLoadingState(73, "Loading entity3");
		_managerPackage.luaEntityParser.parseEntity("./data/scripts/Intrusion/Entities/Entity3.lua");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		_splashScreen.setLoadingState(80, "Initializing application infrastructure");
		_managerPackage.app.initialise(_managerPackage.config.getResolution(), _managerPackage.config.getTitle(), _managerPackage.config.getGameViewScale());
		_managerPackage.inputManager.m_GetWindowSizeCallback = [&_managerPackage]() {
			return sf::Vector2i(_managerPackage.app.getRenderTarget().getSize());
		};

		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		if (_managerPackage.config.m_SkipToLevel && _managerPackage.luaLevelParser.levelHasBeenParsed(_managerPackage.config.m_LevelToSkipTo)) {
			_splashScreen.setLoadingState(90, "Skipping to level: " + _managerPackage.config.m_LevelToSkipTo);

			itr::Level *level = new itr::Level(_managerPackage.entityFactory, _managerPackage.pathfindingService);
			level->initialize(_managerPackage.luaLevelParser.getLevel(_managerPackage.config.m_LevelToSkipTo));
			level->initializeGraphics();

			itr::GameScene *gameScene = new itr::GameScene(_managerPackage.textureManager, _managerPackage.entityManager, _systemPackage.render, _systemPackage.pathFollowing);
			gameScene->m_Level = level;
			_managerPackage.sceneManager.pushScene(gameScene);

			itr::GameUiScene *gameUiScene = new itr::GameUiScene(_managerPackage.fontManager, _managerPackage.textureManager, _managerPackage.inputManager, _managerPackage.config);
			_managerPackage.sceneManager.pushScene(gameUiScene);

			std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT * 10));
		}
		else {
			_splashScreen.setLoadingState(90, "Creating start scene");
			inf::Scene *scene = new itr::StartScene(_managerPackage.fontManager, _managerPackage.textureManager, _managerPackage.config, _managerPackage.inputManager);
			_managerPackage.sceneManager.pushScene(scene);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		_splashScreen.setLoadingState(100, "");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT * 5));
	}

	_splashScreen.close();
}

int main(int _argc, char **_argv) {
	ManagerPackage managerPackage;
	SystemPackage systemPackage;

	inf::SplashScreen splashScreen("./data/textures/Intrusion/splash_screen.png", "./data/fonts/Intrusion/SourceCodePro-Regular.otf");
	
	std::thread splashScreenThread(&inf::SplashScreen::show, &splashScreen);

	loadResources(splashScreen, managerPackage, systemPackage);

	splashScreenThread.join();

	managerPackage.app.start();

	return EXIT_SUCCESS;
}
