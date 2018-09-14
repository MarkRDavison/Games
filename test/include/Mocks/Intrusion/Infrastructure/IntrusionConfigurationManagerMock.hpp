#ifndef INCLUDED_MOCKS_INTRUSION_INFRASTRUCTURE_INTRUSION_CONFIGURATION_MANAGER_MOCK_HPP_
#define INCLUDED_MOCKS_INTRUSION_INFRASTRUCTURE_INTRUSION_CONFIGURATION_MANAGER_MOCK_HPP_

#include <Intrusion/Infrastructure/IntrusionConfigurationManager.hpp>

namespace itr {

	class IntrusionConfigurationManagerMock : public IntrusionConfigurationManager {
	public:
		IntrusionConfigurationManagerMock(inf::LuaManager& _luaManager)
			: IntrusionConfigurationManager(_luaManager) {
			
		}

		float getGameViewScale(void) const override { return scale; }
		
		float scale{ 1.0f };
	};

}

#endif // INCLUDED_MOCKS_INTRUSION_INFRASTRUCTURE_INTRUSION_CONFIGURATION_MANAGER_MOCK_HPP_