#include <Castle/Infrastructure/CastleConfigurationManager.hpp>
#include <Infrastructure/LuaManager.hpp>

namespace castle {

	CastleConfigurationManager::CastleConfigurationManager(inf::LuaManager& _luaManager) :
		inf::ConfigurationManager(_luaManager) {
		
	}

	void CastleConfigurationManager::loadCustomConfigurations(inf::LuaManager& _luaManager) {
		
	}
}
