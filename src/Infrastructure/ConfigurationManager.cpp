#include <Infrastructure/ConfigurationManager.hpp>

#include <Infrastructure/LuaManager.hpp>

namespace inf {
	const std::string ConfigurationManager::Name = "ConfigurationManager";
	const std::string ConfigurationManager::ConfigStateScope = "Config";
	const std::string ConfigurationManager::DefaultTitle = "Zeno - Untitled Game";

	ConfigurationManager::ConfigurationManager(LuaManager& _luaManager) :
		m_GameViewScale(DefaultGameViewScale),
		m_ResolutionX(DefaultResolutionX),
		m_ResolutionY(DefaultResolutionY),
		m_Title(DefaultTitle),
		m_LuaManager(_luaManager){
		m_LuaManager.createState(ConfigStateScope);
	}

	ConfigurationManager::~ConfigurationManager(void) {

	}


	void ConfigurationManager::loadConfiguration(const std::string& _configFilePath) {
		m_PreviousConfigFile = _configFilePath;
		m_LuaManager.runScriptFile(_configFilePath, ConfigStateScope);

		auto& state = m_LuaManager.getState(ConfigStateScope);

		sol::optional<unsigned int> resolutionX = state["config"]["resolution"]["x"];
		if (sol::nullopt != resolutionX) {
			m_ResolutionX = resolutionX.value();
		}
		sol::optional<unsigned int> resolutionY = state["config"]["resolution"]["y"];
		if (sol::nullopt != resolutionY) {
			m_ResolutionY = resolutionY.value();
		}
		sol::optional<std::string> title = state["config"]["title"];
		if (sol::nullopt != title) {
			m_Title = title.value();
		}
		sol::optional<float> gameViewScale = state["config"]["gameViewScale"];
		if (sol::nullopt != gameViewScale) {
			m_GameViewScale = gameViewScale.value();
		}

		loadCustomConfigurations(m_LuaManager);
	}
	void ConfigurationManager::reloadConfiguration(void) {
		loadConfiguration(m_PreviousConfigFile);
	}

	sf::Vector2u ConfigurationManager::getResolution(void) const {
		return { m_ResolutionX, m_ResolutionY };
	}

	std::string ConfigurationManager::getTitle(void) const {
		return m_Title;
	}

	float ConfigurationManager::getGameViewScale(void) const {
		return m_GameViewScale;
	}

}
