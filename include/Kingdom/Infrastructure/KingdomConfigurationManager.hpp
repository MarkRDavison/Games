#ifndef INCLUDED_KINGDOM_INFRASTRUCTURE_KINGDOM_CONFIGURATION_MANAGER_HPP_
#define INCLUDED_KINGDOM_INFRASTRUCTURE_KINGDOM_CONFIGURATION_MANAGER_HPP_

#include <Infrastructure/ConfigurationManager.hpp>

namespace kdm {
	
	class KingdomConfigurationManager : public inf::ConfigurationManager {
	public:
		KingdomConfigurationManager(inf::LuaManager& _luaManager);
		void loadCustomConfigurations(inf::LuaManager& _luaManager) override;		
	};

}

#endif // INCLUDED_KINGDOM_INFRASTRUCTURE_KINGDOM_CONFIGURATION_MANAGER_HPP_