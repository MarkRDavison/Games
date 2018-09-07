#include <Infrastructure/Application.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/LuaManager.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/LuaConsole.hpp>
#include <Infrastructure/Scenes/LuaConsoleScene.hpp>
#include <Kingdom/Infrastructure/KingdomConfigurationManager.hpp>
#include <Kingdom/Infrastructure/Definitions.hpp>
#include <Kingdom/Infrastructure/LuaLevelParser.hpp>
#include <Kingdom/Scenes/GameScene.hpp>
#include <Kingdom/Components/WaypointComponent.hpp>
#include <Infrastructure/Services/PathfindingService.hpp>
#include <Infrastructure/Services/SurfaceService.hpp>


int main(int _argc, char **_argv) {
	inf::FontManager fontManager;
	inf::SceneManager sceneManager;
	inf::TextureManager textureManager;
	inf::LuaManager luaManager;
	inf::InputManager inputManager;
	kdm::LuaLevelParser levelParser(luaManager);

	luaManager.createState(kdm::Definitions::UiLuaStateScope);
	luaManager.createState(kdm::Definitions::LevelParseLuaStateScope);

	inf::LuaConsole luaConsole(kdm::Definitions::UiLuaStateScope, luaManager);

	inf::Application app(fontManager, sceneManager);

	kdm::KingdomConfigurationManager config(luaManager);
	config.loadConfiguration("./data/scripts/Kingdom/config.lua");

	app.initialise(config.getResolution(), config.getTitle(), config.getGameViewScale());

	textureManager.loadTexture("./data/textures/Kingdom/terrain.png", kdm::Definitions::TerrainTextureName);
	textureManager.loadTexture("./data/textures/Kingdom/gear.png", kdm::Definitions::GearTextureName);
	textureManager.loadTexture("./data/textures/Kingdom/main_base.png", kdm::Definitions::MainBaseTextureName);
	textureManager.loadTexture("./data/textures/Kingdom/temp_ore.png", kdm::Definitions::TempOreTextureName);
	textureManager.loadTexture("./data/textures/Kingdom/worker.png", kdm::Definitions::WorkerTextureName);

	ecs::EntityManager entityManager;

	kdm::EntityFactory entityFactory(entityManager, textureManager, config);
	entityFactory.spawnStartingBuilding({ 2, 4 });
	entityFactory.spawnWorker({ 3,4 });
	entityFactory.spawnTempOre({ 6, 5 });
	entityFactory.spawnTempOre({ 1, 11 });
	entityFactory.spawnTempOre({ 21, 8 });

	const inf::PathfindingService pathfindingService;
	inf::SurfaceService surfaceService;

	kdm::RenderSystem renderSystem;
	kdm::MovementSystem movementSystem;
	kdm::WaypointSytem waypointSytem;
	kdm::PathfindingSystem pathfindingSystem(pathfindingService, surfaceService);

	std::function<sf::Vector2f(const sf::Vector2i&)> coordConverter = [&app](const sf::Vector2i& _c) {return app.convertEventCoordsToGameCoords(_c); };

	kdm::GameScene *scene = new kdm::GameScene(coordConverter, entityManager, textureManager, entityFactory, renderSystem, movementSystem, waypointSytem, pathfindingSystem);

	scene->m_Level = new kdm::Level();
	scene->m_Level->initialize(levelParser.parseLevel("./data/scripts/Kingdom/Levels/level1.lua"));
	scene->m_Level->initializeGraphics();

	surfaceService.addSurface(scene->m_Level);
	surfaceService.setCurrentSurface(scene->m_Level->getSurfaceName());

	inf::LuaConsoleScene *consoleScene = new inf::LuaConsoleScene(luaConsole, fontManager);

	sceneManager.pushScene(scene);
	sceneManager.pushScene(consoleScene);

	app.start();

	return EXIT_SUCCESS;
}
