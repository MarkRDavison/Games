#ifndef INCLUDED_MINESWEEPER_INFRASTRUCTURE_CONFIGURATION_MANAGER_HPP_
#define INCLUDED_MINESWEEPER_INFRASTRUCTURE_CONFIGURATION_MANAGER_HPP_

#include <Infrastructure/ConfigurationManager.hpp>

namespace swp {

	class ConfigurationManager : public inf::ConfigurationManager {
	public:
		ConfigurationManager(inf::LuaManager& _luaManager);
		void loadCustomConfigurations(inf::LuaManager& _luaManager) override;
	};

}

#endif // INCLUDED_MINESWEEPER_INFRASTRUCTURE_CONFIGURATION_MANAGER_HPP_