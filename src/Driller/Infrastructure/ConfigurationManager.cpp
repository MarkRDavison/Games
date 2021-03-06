#include <Driller/Infrastructure/ConfigurationManager.hpp>
#include <Infrastructure/LuaManager.hpp>

namespace drl {
	
	ConfigurationManager::ConfigurationManager(inf::LuaManager& _luaManager) :
		inf::ConfigurationManager(_luaManager) {

	}
	ConfigurationManager::~ConfigurationManager(void) {

	}

	void ConfigurationManager::loadCustomConfigurations(inf::LuaManager &_luaManager) {
		sol::state& state = _luaManager.getState(inf::ConfigurationManager::ConfigStateScope);
	}

}