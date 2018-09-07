#ifndef INCLUDED_INTRUSION_INFRASTRUCTURE_INTRUSION_CONFIGURATION_MANAGER_HPP_
#define INCLUDED_INTRUSION_INFRASTRUCTURE_INTRUSION_CONFIGURATION_MANAGER_HPP_

#include <Infrastructure/ConfigurationManager.hpp>

namespace itr {

	class IntrusionConfigurationManager : public inf::ConfigurationManager {
	public:
		IntrusionConfigurationManager(inf::LuaManager& _luaManager);
		void loadCustomConfigurations(inf::LuaManager& _luaManager) override;

		bool m_SkipToLevel{false};
		std::string m_LevelToSkipTo;
	};

}

#endif // INCLUDED_INTRUSION_INFRASTRUCTURE_INTRUSION_CONFIGURATION_MANAGER_HPP_