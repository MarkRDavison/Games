#ifndef INCLUDED_PACMAN_INFRASTRUCTURE_PACMAN_CONFIGURATION_MANAGER_HPP_
#define INCLUDED_PACMAN_INFRASTRUCTURE_PACMAN_CONFIGURATION_MANAGER_HPP_

#include <Infrastructure/ConfigurationManager.hpp>

namespace pacman {

	class PacmanConfigurationManager : public inf::ConfigurationManager {
	public:

		static const constexpr unsigned int DefaultGameWidth = 12;
		static const constexpr unsigned int DefaultGameHeight = 10;
		static const constexpr float DefaultInitialTickSpeed = 1.0f;

		PacmanConfigurationManager(inf::LuaManager& _luaManager);
		~PacmanConfigurationManager(void) override;

		void loadCustomConfigurations(inf::LuaManager& _luaManager) override;


	private:
	};
}

#endif // INCLUDED_PACMAN_INFRASTRUCTURE_PACMAN_CONFIGURATION_MANAGER_HPP_