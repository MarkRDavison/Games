#ifndef INCLUDED_CASTLE_INFRASTRUCTURE_CASTLE_CONFIGURATION_MANAGER_HPP_
#define INCLUDED_CASTLE_INFRASTRUCTURE_CASTLE_CONFIGURATION_MANAGER_HPP_

#include <Infrastructure/ConfigurationManager.hpp>

namespace castle {
	class CastleConfigurationManager : public inf::ConfigurationManager {
	public:
		CastleConfigurationManager(inf::LuaManager& _luaManager);
		void loadCustomConfigurations(inf::LuaManager& _luaManager) override;
	};
}

#endif // INCLUDED_CASTLE_INFRASTRUCTURE_CASTLE_CONFIGURATION_MANAGER_HPP_