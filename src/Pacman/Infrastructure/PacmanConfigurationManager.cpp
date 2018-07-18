#include <Pacman/Infrastructure/PacmanConfigurationManager.hpp>
#include <Infrastructure/LuaManager.hpp>

namespace pacman {


	PacmanConfigurationManager::PacmanConfigurationManager(inf::LuaManager& _luaManager) :
		inf::ConfigurationManager(_luaManager) {
		
	}
	PacmanConfigurationManager::~PacmanConfigurationManager(void) {
		
	}

	void PacmanConfigurationManager::loadCustomConfigurations(inf::LuaManager& _luaManager) {
		auto& state = _luaManager.getState(inf::LuaManager::DefaultStateScope);
	}
}