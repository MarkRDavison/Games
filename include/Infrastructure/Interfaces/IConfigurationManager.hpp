#ifndef INCLUDED_EXPEDITION_INFRASTRUCTURE_INTERFACES_I_CONFIGURATION_MANAGER_HPP_
#define INCLUDED_EXPEDITION_INFRASTRUCTURE_INTERFACES_I_CONFIGURATION_MANAGER_HPP_

#include <string>
#include <SFML/System/Vector2.hpp>

namespace inf {
	
	class LuaManager;

	class IConfigurationManager {
	public:
		virtual ~IConfigurationManager(void) = 0 {}

		virtual void loadCustomConfigurations(LuaManager& _luaManager) = 0;

		virtual sf::Vector2u getResolution(void) const = 0;
		virtual std::string getTitle(void) const = 0;
		virtual float getGameViewScale(void) const = 0;
	};

}

#endif // INCLUDED_EXPEDITION_INFRASTRUCTURE_INTERFACES_I_CONFIGURATION_MANAGER_HPP_