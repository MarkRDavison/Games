#include <Arkanoid/Infrastructure/ArkanoidConfigurationManager.hpp>

namespace ark {

	ArkanoidConfigurationManager::ArkanoidConfigurationManager(inf::LuaManager& _luaManager) :
		ConfigurationManager(_luaManager) {

	}
	ArkanoidConfigurationManager::~ArkanoidConfigurationManager(void) {

	}

	void ArkanoidConfigurationManager::loadCustomConfigurations(inf::LuaManager& _luaManager) {

	}
}