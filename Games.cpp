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
#include <Castle/Scenes/DebugOverlayScene.hpp>
#include <Castle/Scenes/PlayerCollisionTestScene.hpp>
#include <Castle/Systems/PlayerControlSystem.hpp>

#include <Hurricane/Scenes/GameScene.hpp>
#include <Hurricane/Infrastructure/HurricaneConfigurationManager.hpp>
#include <Hurricane/Scenes/DebugOverlayGameScene.hpp>
#include <Hurricane/Infrastructure/Definitions.hpp>
#include <Hurricane/Infrastructure/LuaDataParser.hpp>
#include <Hurricane/Systems/PickupControlSystem.hpp>

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

	fontManager.loadFont("./data/fonts/Castle/SourceCodePro-Regular.otf", "source_code_pro_regular");

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

	castle::DebugOverlayScene *overlayScene = new castle::DebugOverlayScene(fontManager);
	sceneManager.pushScene(overlayScene);

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

void runHurricane(void) {

	inf::FontManager fontManager;
	inf::SceneManager sceneManager;
	inf::TextureManager textureManager;
	inf::LuaManager luaManager;
	inf::InputManager inputManager;

	ecs::EntityManager entityManager;

	inf::Application app(fontManager, sceneManager);

	hur::LuaDataParser dataParser(luaManager);
	hur::HurricaneConfigurationManager configurationManager = hur::HurricaneConfigurationManager(luaManager);

	configurationManager.loadConfiguration("./data/scripts/Hurricane/config.lua");
	dataParser.parseDropTables("./data/scripts/Hurricane/DropTables.lua");

	textureManager.loadTexture("./data/textures/Hurricane/Lasers/laserRed01.png", "laser_red");
	textureManager.loadTexture("./data/textures/Hurricane/Lasers/laserGreen11.png", "laser_green");
	textureManager.loadTexture("./data/textures/Hurricane/Lasers/laserBlue01.png", hur::Definitions::BlueLaserTextureName);
	textureManager.loadTexture("./data/textures/Hurricane/playerShip1_blue.png", hur::Definitions::BluePlayerShip);
	textureManager.loadTexture("./data/textures/Hurricane/Enemies/enemyBlack1.png", hur::Definitions::EnemyShipBlack1);
	textureManager.loadTexture("./data/textures/Hurricane/Enemies/enemyBlack2.png", hur::Definitions::EnemyShipBlack2);
	textureManager.loadTexture("./data/textures/Hurricane/Enemies/enemyBlack3.png", hur::Definitions::EnemyShipBlack3);
	textureManager.loadTexture("./data/textures/Hurricane/Enemies/enemyBlack4.png", hur::Definitions::EnemyShipBlack4);
	textureManager.loadTexture("./data/textures/Hurricane/Enemies/enemyBlack5.png", hur::Definitions::EnemyShipBlack5);
	textureManager.loadTexture("./data/textures/Hurricane/Power-ups/bolt_gold.png", hur::Definitions::BoltGold);
	textureManager.loadTexture("./data/textures/Hurricane/Power-ups/bolt_silver.png", hur::Definitions::BoltSilver);
	textureManager.loadTexture("./data/textures/Hurricane/Power-ups/bolt_bronze.png", hur::Definitions::BoltBronze);
	textureManager.loadTexture("./data/textures/Hurricane/Power-ups/pill_blue.png", hur::Definitions::PillBlue);
	textureManager.loadTexture("./data/textures/Hurricane/Power-ups/pill_green.png", hur::Definitions::PillGreen);
	textureManager.loadTexture("./data/textures/Hurricane/Power-ups/pill_red.png", hur::Definitions::PillRed);
	textureManager.loadTexture("./data/textures/Hurricane/Power-ups/pill_yellow.png", hur::Definitions::PillYellow);

	app.initialise(configurationManager.getResolution(), configurationManager.getTitle(), configurationManager.getGameViewScale());

	hur::EntityFactory entityFactory(textureManager, dataParser);
	hur::CollisionSystem collisionSystem(entityFactory);
	hur::KinematicSystem kinematicSystem;
	hur::PlayerControlSystem playerControlSystem(inputManager, textureManager);
	hur::ProjectileControlSystem projectileControlSystem;
	hur::PickupControlSystem pickupControlSystem;

	hur::GameScene *gameScene = new hur::GameScene(textureManager, collisionSystem, kinematicSystem, playerControlSystem, projectileControlSystem, pickupControlSystem, entityFactory);
	hur::DebugOverlayGameScene *debugOverlayGameScene = new hur::DebugOverlayGameScene(entityManager, fontManager);

	gameScene->m_Level = new hur::Level(entityManager);
	gameScene->addPlayer();
	gameScene->addEnemy(0, { 4.0f, 5.0f });
	gameScene->addEnemy(1, { 7.0f, 5.0f });
	gameScene->addEnemy(2, { 10.0f, 5.0f });
	gameScene->addEnemy(3, { 13.0f, 5.0f });
	gameScene->addEnemy(4, { 16.0f, 5.0f });

	sceneManager.pushScene(gameScene);
	sceneManager.pushScene(debugOverlayGameScene);

	app.start();
}

int main(int _argc, char **_argv) {
	//runArkanoid();
	//runSnake();
	//runPacman();

	//runCastleTestScene();
	//runCastle();

	runHurricane();
}
