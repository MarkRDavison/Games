#ifndef INCLUDED_EXPEDITION_INFRASTRUCTURE_CONFIGURATION_MANAGER_HPP_
#define INCLUDED_EXPEDITION_INFRASTRUCTURE_CONFIGURATION_MANAGER_HPP_

#include <string>
#include <SFML/System/Vector2.hpp>
#include <Infrastructure/Interfaces/IConfigurationManager.hpp>

namespace inf {
	class LuaManager;

	class ConfigurationManager : public IConfigurationManager {
	public:
		static const std::string Name;
		static const std::string ConfigStateScope;

		static const std::string DefaultTitle;

		static const constexpr unsigned int DefaultResolutionX = 1280;
		static const constexpr unsigned int DefaultResolutionY = 720;
		static const constexpr float DefaultGameViewScale = 50.0f;

		ConfigurationManager(LuaManager& _luaManager);
		virtual ~ConfigurationManager(void) override;

		void loadConfiguration(const std::string& _configFilePath);
		void reloadConfiguration(void);
		void loadCustomConfigurations(LuaManager& _luaManager) override {}

		sf::Vector2u getResolution(void) const override;
		std::string getTitle(void) const override;
		float getGameViewScale(void) const override;

	private:

		float m_GameViewScale;
		unsigned int m_ResolutionX;
		unsigned int m_ResolutionY;
		std::string m_Title;

		std::string m_PreviousConfigFile;
		LuaManager& m_LuaManager;
	};
} 

#endif // INCLUDED_EXPEDITION_INFRASTRUCTURE_CONFIGURATION_MANAGER_HPP_