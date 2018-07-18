#ifndef INCLUDED_ARKANOID_INFRASTRUCTURE_ARKANOID_CONFIGURATION_MANAGER_HPP_
#define INCLUDED_ARKANOID_INFRASTRUCTURE_ARKANOID_CONFIGURATION_MANAGER_HPP_

#include <Infrastructure/ConfigurationManager.hpp>

namespace ark {
	class ArkanoidConfigurationManager : public inf::ConfigurationManager {
	public:
		ArkanoidConfigurationManager(inf::LuaManager& _luaManager);
		~ArkanoidConfigurationManager(void) override;

		void loadCustomConfigurations(inf::LuaManager& _luaManager) override;
	};
}

#endif // INCLUDED_ARKANOID_INFRASTRUCTURE_ARKANOID_CONFIGURATION_MANAGER_HPP_