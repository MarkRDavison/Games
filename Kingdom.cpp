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
#include <Kingdom/Infrastructure/KingdomEntityGroups.hpp>
#include <Kingdom/Components/PositionComponent.hpp>
#include <Kingdom/Components/SpriteComponent.hpp>
#include <Kingdom/Components/MovementComponent.hpp>
#include <Kingdom/Components/WaypointComponent.hpp>
#include <Kingdom/Components/PathfindingComponent.hpp>
#include <Kingdom/Services/PathfindingService.hpp>
#include <Kingdom/Services/SurfaceService.hpp>


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

	ecs::EntityManager entityManager;

	kdm::EntityFactory entityFactory(entityManager);

	const kdm::PathfindingService pathfindingService;
	kdm::SurfaceService surfaceService;

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

	{
		ecs::Entity& e = entityManager.addEntity("Gear");
		e.addGroup(kdm::EntityGroup::GRenderable);
		e.addGroup(kdm::EntityGroup::GMoveable);
		e.addGroup(kdm::EntityGroup::GWaypoint);
		e.addGroup(kdm::EntityGroup::GPathfindable);
		e.addComponent<kdm::PositionComponent>(sf::Vector2f(4.5f, 4.5f));
		e.addComponent<kdm::MovementComponent>().speed = 4.0f;
		e.addComponent<kdm::WaypointComponent>();
		e.addComponent<kdm::PathfindingComponent>();
		e.addComponent<kdm::SpriteComponent>(textureManager.getTexture(kdm::Definitions::GearTextureName), sf::IntRect(0, 0, 64, 64), config.getGameViewScale()).visualOffset = {0.0f, 32.0f};
	}

	app.start();

	return EXIT_SUCCESS;
}
