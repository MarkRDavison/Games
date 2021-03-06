#define SOL_CHECK_ARGUMENTS 1

#include <Infrastructure/Application.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/LuaManager.hpp>

#include <EntityComponentSystem/Entity.hpp>

#include <Snake/Infrastructure/SnakeConfigurationManager.hpp>
#include <Snake/Scenes/GameScene.hpp>

#include <Arkanoid/Infrastructure/ArkanoidConfigurationManager.hpp>
#include <Arkanoid/Scenes/GameScene.hpp>

#include <Pacman/Infrastructure/PacmanConfigurationManager.hpp>
#include <Pacman/Scenes/GameScene.hpp>
#include <Pacman/Infrastructure/BoardFactory.hpp>

void runSnake(void) {
	inf::FontManager fontManager;
	inf::SceneManager sceneManager;
	inf::TextureManager textureManager;
	inf::LuaManager luaManager;
	inf::InputManager inputManager;

	inf::Application app(fontManager, sceneManager);
	snake::SnakeConfigurationManager configurationManager = snake::SnakeConfigurationManager(luaManager);
	configurationManager.loadConfiguration("./data/scripts/Snake/config.lua");
	app.initialise(configurationManager.getResolution(), configurationManager.getTitle(), configurationManager.getGameViewScale());

	snake::GameScene *gameScene = new snake::GameScene(configurationManager);
	gameScene->initialize();
	sceneManager.pushScene(gameScene);

	app.start();
}

void runArkanoid(void) {
	inf::FontManager fontManager;
	inf::SceneManager sceneManager;
	inf::TextureManager textureManager;
	inf::LuaManager luaManager;
	inf::InputManager inputManager;

	inf::Application app(fontManager, sceneManager);
	ark::ArkanoidConfigurationManager configurationManager = ark::ArkanoidConfigurationManager(luaManager);
	configurationManager.loadConfiguration("./data/scripts/Arkanoid/config.lua");
	app.initialise(configurationManager.getResolution(), configurationManager.getTitle(), configurationManager.getGameViewScale());

	ark::GameScene *gameScene = new ark::GameScene();
	sceneManager.pushScene(gameScene);

	app.start();
}

void runPacman(void) {
	inf::FontManager fontManager;
	inf::SceneManager sceneManager;
	inf::TextureManager textureManager;
	inf::LuaManager luaManager;
	inf::InputManager inputManager;

	textureManager.loadTexture("./data/textures/Pacman/spritemap.png", "spritemap");

	inf::Application app(fontManager, sceneManager);
	pacman::PacmanConfigurationManager configurationManager = pacman::PacmanConfigurationManager(luaManager);
	configurationManager.loadConfiguration("./data/scripts/Pacman/config.lua");
	app.initialise(configurationManager.getResolution(), configurationManager.getTitle(), configurationManager.getGameViewScale());
	auto *b = pacman::BoardFactory::createStandardBoard();
	pacman::GameScene *gameScene = new pacman::GameScene(textureManager, b);
	gameScene->initialize();
	sceneManager.pushScene(gameScene);

	app.start();
	
}

int main(int _argc, char **_argv) {
	//runArkanoid();
	//runSnake();
	//runPacman();
}
