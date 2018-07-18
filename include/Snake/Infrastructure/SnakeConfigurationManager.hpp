#ifndef INCLUDED_SNAKE_INFRASTRUCTURE_SNAKE_CONFIGURATION_MANAGER_HPP_
#define INCLUDED_SNAKE_INFRASTRUCTURE_SNAKE_CONFIGURATION_MANAGER_HPP_

#include <Infrastructure/ConfigurationManager.hpp>

namespace snake {
	class SnakeConfigurationManager : public inf::ConfigurationManager {
	public:

		static const constexpr unsigned int DefaultGameWidth = 12;
		static const constexpr unsigned int DefaultGameHeight = 10;
		static const constexpr float DefaultInitialTickSpeed = 1.0f;

		SnakeConfigurationManager(inf::LuaManager& _luaManager);
		~SnakeConfigurationManager(void) override;

		void loadCustomConfigurations(inf::LuaManager& _luaManager) override;

		unsigned int GetGameWidth(void) const;
		unsigned int GetGameHeight(void) const;
		float getInitialTickSpeed(void) const;

	private:
		unsigned int m_GameWidth;
		unsigned int m_GameHeight;
		float m_InitialTickSpeed;
	};
}

#endif // INCLUDED_SNAKE_INFRASTRUCTURE_SNAKE_CONFIGURATION_MANAGER_HPP_