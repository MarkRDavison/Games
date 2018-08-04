#ifndef INCLUDED_HURRICANE_INFRSTRUCTURE_HURRICANE_CONFIGURATION_MANAGER_HPP_
#define INCLUDED_HURRICANE_INFRSTRUCTURE_HURRICANE_CONFIGURATION_MANAGER_HPP_

#include <Infrastructure/ConfigurationManager.hpp>

namespace hur {
	class HurricaneConfigurationManager : public inf::ConfigurationManager {
	public:
		HurricaneConfigurationManager(inf::LuaManager& _luaManager);
		void loadCustomConfigurations(inf::LuaManager& _luaManager) override;
	};
}

#endif // INCLUDED_HURRICANE_INFRSTRUCTURE_HURRICANE_CONFIGURATION_MANAGER_HPP_