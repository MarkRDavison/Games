#ifndef INCLUDED_SOVEREIGN_INFRASTRUCTURE_CONFIGURATION_MANAGER_HPP_
#define INCLUDED_SOVEREIGN_INFRASTRUCTURE_CONFIGURATION_MANAGER_HPP_

#include <Infrastructure/ConfigurationManager.hpp>

namespace sov {

	class ConfigurationManager : public inf::ConfigurationManager {
	public:
		ConfigurationManager(inf::LuaManager& _luaManager);
		~ConfigurationManager(void) override;

		virtual void loadCustomConfigurations(inf::LuaManager &_luaManager);
	};

}

#endif // INCLUDED_SOVEREIGN_INFRASTRUCTURE_CONFIGURATION_MANAGER_HPP_