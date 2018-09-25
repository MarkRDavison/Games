#include <cstdlib>
#include <Infrastructure/Application.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/LuaManager.hpp>
#include <Pollution/Infrastructure/ConfigurationManager.hpp>
#include <Pollution/Infrastructure/Definitions.hpp>
#include <Pollution/Scenes/GameScene.hpp>
#include <Infrastructure/Services/ResourceService.hpp>

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

	ServicePackage(ManagerPackage& _managerPackage) {

	}

	inf::ResourceService resource;
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

	pol::GameScene *scene = new pol::GameScene(managerPackage.inputManager, managerPackage.config);

	pol::WorldDataInitialisationPackage worldData{};
	worldData.Sides = 36;
	worldData.SnapMargin = 0.2f;
	scene->initialise(worldData);

	managerPackage.sceneManager.pushScene(scene);

	managerPackage.app.start();

	return EXIT_SUCCESS;
}