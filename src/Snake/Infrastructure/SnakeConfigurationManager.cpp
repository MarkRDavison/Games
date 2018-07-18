#include <Snake/Infrastructure/SnakeConfigurationManager.hpp>

#include <Infrastructure/LuaManager.hpp>


namespace snake {

	SnakeConfigurationManager::SnakeConfigurationManager(inf::LuaManager& _luaManager) :
		inf::ConfigurationManager(_luaManager),
		m_GameWidth(DefaultGameWidth),
		m_GameHeight(DefaultGameHeight),
		m_InitialTickSpeed(DefaultInitialTickSpeed) {
		
	}
	SnakeConfigurationManager::~SnakeConfigurationManager(void) {
		
	}

	void SnakeConfigurationManager::loadCustomConfigurations(inf::LuaManager& _luaManager) {
		auto& state = _luaManager.getState(inf::LuaManager::DefaultStateScope);

		sol::optional<unsigned int> gameWidth = state["config"]["game"]["width"];
		if (sol::nullopt != gameWidth) {
			m_GameWidth = gameWidth.value();
		}

		sol::optional<unsigned int> gameHeight = state["config"]["game"]["height"];
		if (sol::nullopt != gameHeight) {
			m_GameHeight = gameHeight.value();
		}

		sol::optional<float> tickSpeed = state["config"]["game"]["tickspeed"];
		if (sol::nullopt != tickSpeed) {
			m_GameHeight = tickSpeed.value();
		}
	}

	unsigned int SnakeConfigurationManager::GetGameWidth(void) const {
		return m_GameWidth;
	}
	unsigned int SnakeConfigurationManager::GetGameHeight(void) const {
		return m_GameHeight;
	}

	float SnakeConfigurationManager::getInitialTickSpeed() const {
		return m_InitialTickSpeed;
	}
}
