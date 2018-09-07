#include <cstdlib>

#include <Infrastructure/FontManager.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/LuaManager.hpp>
#include <Infrastructure/SceneManager.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/Application.hpp>
#include <Infrastructure/SplashScreen.hpp>

#include <EntityComponentSystem/EntityManager.hpp>

#include <Intrusion/Infrastructure/IntrusionConfigurationManager.hpp>
#include <Intrusion/Infrastructure/IntrusionDefinitions.hpp>
#include <Intrusion/Infrastructure/LuaLevelParser.hpp>
#include <Intrusion/Scenes/StartScene.hpp>
#include <Intrusion/Scenes/GameScene.hpp>
#include <Intrusion/Infrastructure/EntityFactory.hpp>

#define ARTIFICIAL_WAIT 150

struct ManagerPackage {

	ManagerPackage() :
		config(luaManager),
		app(fontManager, sceneManager),
		luaLevelParser(luaManager),
		entityFactory(entityManager) {
	}

	inf::FontManager fontManager;
	inf::SceneManager sceneManager;
	inf::TextureManager textureManager;
	inf::LuaManager luaManager;
	inf::InputManager inputManager;
	itr::IntrusionConfigurationManager config;
	inf::Application app;

	ecs::EntityManager entityManager; 
	
	itr::LuaLevelParser luaLevelParser;
	itr::EntityFactory entityFactory;
};

void loadResources(inf::SplashScreen& _splashScreen, ManagerPackage& _package) {
	{
		_splashScreen.setLoadingState(0, "Loading configuration");
		_package.luaManager.createState(itr::Definitions::LevelParseLuaStateScope);
		_package.config.loadConfiguration("./data/scripts/Intrusion/config.lua");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		_splashScreen.setLoadingState(10, "Loading textures");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
		_splashScreen.setLoadingState(11, "Loading texture 'terrain'");
		_package.textureManager.loadTexture("./data/textures/Intrusion/terrain.png", itr::Definitions::TerrainTextureName);
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
		_splashScreen.setLoadingState(11, "Loading texture 'spear_icon'");
		_package.textureManager.loadTexture("./data/textures/Intrusion/spear_icon.png", itr::Definitions::SpearIconTextureName);
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
		_package.luaLevelParser.parseLevel("./data/scripts/Intrusion/Levels/Level1.lua");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
		_splashScreen.setLoadingState(52, "Loading level2");
		_package.luaLevelParser.parseLevel("./data/scripts/Intrusion/Levels/Level2.lua");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
		_splashScreen.setLoadingState(53, "Loading level3");
		_package.luaLevelParser.parseLevel("./data/scripts/Intrusion/Levels/Level3.lua");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
		_splashScreen.setLoadingState(54, "Loading level4");
		_package.luaLevelParser.parseLevel("./data/scripts/Intrusion/Levels/Level4.lua");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		_splashScreen.setLoadingState(60, "Loading tower prototypes");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		_splashScreen.setLoadingState(70, "Loading enemy prototypes");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		_splashScreen.setLoadingState(80, "Initializing application infrastructure");
		_package.app.initialise(_package.config.getResolution(), _package.config.getTitle(), _package.config.getGameViewScale());
		_package.inputManager.m_GetWindowSizeCallback = [&_package]() {
			return sf::Vector2i(_package.app.getRenderTarget().getSize());
		};

		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		inf::Scene *scene;

		if (_package.config.m_SkipToLevel && _package.luaLevelParser.levelHasBeenParsed(_package.config.m_LevelToSkipTo)) {
			_splashScreen.setLoadingState(90, "Skipping to level: " + _package.config.m_LevelToSkipTo);

			itr::Level *level = new itr::Level(_package.entityFactory);
			level->initialize(_package.luaLevelParser.getLevel(_package.config.m_LevelToSkipTo));
			level->initializeGraphics();

			scene = new itr::GameScene(_package.textureManager, _package.entityManager);
			static_cast<itr::GameScene*>(scene)->m_Level = level;
			std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT * 20));
		}
		else {
			_splashScreen.setLoadingState(90, "Creating start scene");
			scene = new itr::StartScene(_package.fontManager, _package.textureManager, _package.config, _package.inputManager);
		}
		_package.sceneManager.pushScene(scene);

		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}
	{
		_splashScreen.setLoadingState(100, "");
		std::this_thread::sleep_for(std::chrono::milliseconds(ARTIFICIAL_WAIT));
	}

	_splashScreen.close();
}

int main(int _argc, char **_argv) {
	ManagerPackage package;

	inf::SplashScreen splashScreen("./data/textures/Intrusion/splash_screen.png", "./data/fonts/Intrusion/SourceCodePro-Regular.otf");
	
	std::thread splashScreenThread(&inf::SplashScreen::show, &splashScreen);

	loadResources(splashScreen, package);

	splashScreenThread.join();

	package.app.start();

	return EXIT_SUCCESS;
}
