#include <Hurricane/Infrastructure/HurricaneConfigurationManager.hpp>
#include <Infrastructure/LuaManager.hpp>

namespace hur {

	HurricaneConfigurationManager::HurricaneConfigurationManager(inf::LuaManager& _luaManager) :
		inf::ConfigurationManager(_luaManager) {
		
	}
	void HurricaneConfigurationManager::loadCustomConfigurations(inf::LuaManager& _luaManager) {
		
	}
}