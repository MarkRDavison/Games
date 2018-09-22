#include <Minesweeper/Infrastructure/ConfigurationManager.hpp>
#include <Infrastructure/LuaManager.hpp>

namespace swp {

	ConfigurationManager::ConfigurationManager(inf::LuaManager& _luaManager) :
		inf::ConfigurationManager(_luaManager) {
		
	}

	void ConfigurationManager::loadCustomConfigurations(inf::LuaManager& _luaManager) {
		sol::state& state = _luaManager.getState(inf::ConfigurationManager::ConfigStateScope);
	}

}
