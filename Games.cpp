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

#include <Castle/Infrastructure/CastleConfigurationManager.hpp>
#include <Castle/Infrastructure/AutoPlayerInputManager.hpp>
#include <Castle/Infrastructure/LuaLevelParser.hpp>
#include <Castle/Infrastructure/LevelTransitionCoordinator.hpp>
#include <Castle/Scenes/GameScene.hpp>
#include <Castle/Scenes/PlayerCollisionTestScene.hpp>
#include <Castle/Systems/PlayerControlSystem.hpp>

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

	pacman::GameScene *gameScene = new pacman::GameScene(textureManager, pacman::BoardFactory::createStandardBoard());
	gameScene->initialize();
	sceneManager.pushScene(gameScene);

	app.start();
	
}

void runCastle(void) {
	inf::FontManager fontManager;
	inf::SceneManager sceneManager;
	inf::TextureManager textureManager;
	inf::LuaManager luaManager;
	inf::InputManager inputManager;

	ecs::EntityManager entityManager;

	textureManager.loadTexture("./data/textures/Castle/player.png", "player");
	textureManager.loadTexture("./data/textures/Castle/terrain.png", "terrain");
	textureManager.loadTexture("./data/textures/Castle/spike.png", "spike");
	textureManager.loadTexture("./data/textures/Castle/coin.png", "coin");
	textureManager.loadTexture("./data/textures/Castle/flame.png", "flame");

	inf::Application app(fontManager, sceneManager);
	castle::CastleConfigurationManager configurationManager = castle::CastleConfigurationManager(luaManager);
	configurationManager.loadConfiguration("./data/scripts/Castle/config.lua");
	app.initialise(configurationManager.getResolution(), configurationManager.getTitle(), configurationManager.getGameViewScale());

	castle::LuaLevelParser parser(luaManager);
	castle::EntityPrototypeFactory prototypeFactory(textureManager);
	castle::CollisionSystem collisionSystem;
	castle::KinematicSystem kinematicSystem;
	castle::PlayerControlSystem playerControlSystem(castle::GPlayer, inputManager);
	castle::PlayerInteractionSystem playerInteractionSystem;
	castle::WaypointSystem waypointSystem;
	castle::LevelTransitionCoordinator levelTransitionCoordinator(prototypeFactory);

	castle::GameScene *gameScene = new castle::GameScene(textureManager, inputManager, configurationManager, collisionSystem, kinematicSystem, playerControlSystem, playerInteractionSystem, waypointSystem, prototypeFactory, levelTransitionCoordinator);
	levelTransitionCoordinator.addParsedLevel(parser.parseLevel("./data/scripts/Castle/Levels/level1.lua"));
	levelTransitionCoordinator.addParsedLevel(parser.parseLevel("./data/scripts/Castle/Levels/level2.lua"));
	levelTransitionCoordinator.addParsedLevel(parser.parseLevel("./data/scripts/Castle/Levels/level3.lua"));
	levelTransitionCoordinator.addParsedLevel(parser.parseLevel("./data/scripts/Castle/Levels/level4.lua"));
	gameScene->setActiveLevel("Level 1");
	gameScene->addPlayer();

	sceneManager.pushScene(gameScene);

	app.start();
}

void runCastleTestScene(void) {
	inf::FontManager fontManager;
	inf::SceneManager sceneManager;
	inf::TextureManager textureManager;
	inf::LuaManager luaManager;
	castle::AutoPlayerInputManager inputManager;

	ecs::EntityManager entityManager;

	textureManager.loadTexture("./data/textures/Castle/terrain.png", "terrain");
	textureManager.loadTexture("./data/textures/Castle/player.png", "player");
	textureManager.loadTexture("./data/textures/Castle/flame.png", "flame");
	textureManager.loadTexture("./data/textures/Castle/spike.png", "spike");
	textureManager.loadTexture("./data/textures/Castle/coin.png", "coin");

	inf::Application app(fontManager, sceneManager);
	castle::CastleConfigurationManager configurationManager = castle::CastleConfigurationManager(luaManager);
	configurationManager.loadConfiguration("./data/scripts/Castle/config.lua");
	app.initialise(configurationManager.getResolution(), configurationManager.getTitle(), configurationManager.getGameViewScale());
	
	castle::CollisionSystem collisionSystem;
	castle::KinematicSystem kinematicSystem;
	castle::PlayerControlSystem playerControlSystem(castle::GPlayer, inputManager);
	castle::PlayerInteractionSystem playerInteractionSystem;
	castle::WaypointSystem waypointSystem;

	castle::PlayerCollisionTestScene *gameScene = new castle::PlayerCollisionTestScene(textureManager, inputManager, configurationManager, entityManager, collisionSystem, kinematicSystem, playerControlSystem, playerInteractionSystem, waypointSystem);
	gameScene->initializeTestScene1();
	sceneManager.pushScene(gameScene);

	app.start();
}

int main(int _argc, char **_argv) {
	//runArkanoid();
	//runSnake();
	//runPacman();

	//runCastleTestScene();
	runCastle();
}
