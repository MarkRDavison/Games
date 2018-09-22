#include <Hurricane/Objects/Level.hpp>
#include <Hurricane/Scenes/DebugOverlayGameScene.hpp>
#include <Hurricane/Scenes/GameScene.hpp>
#include <Hurricane/Infrastructure/Definitions.hpp>
#include <Hurricane/Infrastructure/HurricaneConfigurationManager.hpp>
#include <Infrastructure/Application.hpp>

int main(int _argc, char **_argv) {


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

	return EXIT_SUCCESS;
}
