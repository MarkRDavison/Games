#include <Castle/Infrastructure/CastleConfigurationManager.hpp>
#include <Castle/Infrastructure/LuaLevelParser.hpp>
#include <Castle/Infrastructure/LevelTransitionCoordinator.hpp>
#include <Castle/Scenes/GameScene.hpp>
#include <Castle/Scenes/DebugOverlayScene.hpp>
#include <Castle/Scenes/PlayerCollisionTestScene.hpp>
#include <Castle/Systems/PlayerControlSystem.hpp>
#include <Infrastructure/Application.hpp>


int main(int _arc, char **_argv) {

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

	return EXIT_SUCCESS;
}
