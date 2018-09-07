#include <Intrusion/Infrastructure/IntrusionConfigurationManager.hpp>
#include <Infrastructure/LuaManager.hpp>

namespace itr {

	IntrusionConfigurationManager::IntrusionConfigurationManager(inf::LuaManager& _luaManager) :
		inf::ConfigurationManager(_luaManager) {
		
	}
	void IntrusionConfigurationManager::loadCustomConfigurations(inf::LuaManager& _luaManager) {
		sol::state& state = _luaManager.getState(inf::ConfigurationManager::ConfigStateScope);
		
		sol::optional<std::string> skipToLevelValue = state["config"]["skip_to_level"];
		if (sol::nullopt != skipToLevelValue) {
			m_LevelToSkipTo = skipToLevelValue.value();
			m_SkipToLevel = m_LevelToSkipTo.size() > 0;
		}
	}

}