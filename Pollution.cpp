#include <cstdlib>
#include <Infrastructure/Application.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/LuaManager.hpp>
#include <Pollution/Infrastructure/ConfigurationManager.hpp>
#include <Pollution/Infrastructure/Definitions.hpp>
#include <Pollution/Scenes/GameScene.hpp>
#include <Infrastructure/Services/ResourceService.hpp>
#include <Pollution/Services/WorldUpdateService.hpp>
#include <Pollution/Services/WorldInteractionService.hpp>

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
	
	pol::ConfigurationManager config;
};

struct ServicePackage {

	ServicePackage(ManagerPackage& _managerPackage) :
		worldUpdate(resource),
		worldInteraction(_managerPackage.inputManager, _managerPackage.config, resource) {

	}

	inf::ResourceService resource;

	pol::WorldUpdateService worldUpdate;
	pol::WorldInteractionService worldInteraction;
};

int main(int _argc, char **_argv) {

	ManagerPackage managerPackage;
	ServicePackage servicePackage(managerPackage);

	managerPackage.luaManager.createState(pol::Definitions::GameLuaScope);
	managerPackage.config.loadConfiguration("./data/scripts/Pollution/config.lua");

	managerPackage.app.initialise(managerPackage.config.getResolution(), managerPackage.config.getTitle(), managerPackage.config.getGameViewScale());
	managerPackage.inputManager.m_GetWindowSizeCallback = [&managerPackage]() {
		return sf::Vector2i(managerPackage.app.getRenderTarget().getSize());
	};
	managerPackage.inputManager.m_GetMousePositionCallback = [&managerPackage]() {
		return sf::Mouse::getPosition(managerPackage.app.getWindow());
	};

	managerPackage.textureManager.loadTexture("./data/textures/Pollution/test_planet.png", pol::Definitions::TestSunTextureName);
	managerPackage.textureManager.loadTexture("./data/textures/Pollution/building_sprite_sheet.png", pol::Definitions::BuildingTextureName);

	pol::GameScene *scene = new pol::GameScene(managerPackage.inputManager, managerPackage.fontManager, managerPackage.textureManager, servicePackage.resource, managerPackage.config, servicePackage.worldUpdate, servicePackage.worldInteraction);

	pol::WorldDataInitialisationPackage worldData{};
	worldData.Sides = 24;
	worldData.SnapMargin = 0.2f;
	worldData.rotationRate = 12.5f;
	worldData.rotation = 0.0f;
	scene->initialise(worldData);
	scene->getWorldObject().setWorldTexture(managerPackage.textureManager.getTexture(pol::Definitions::TestSunTextureName));

	managerPackage.sceneManager.pushScene(scene);

	managerPackage.app.start();

	return EXIT_SUCCESS;
}