#ifndef INCLUDED_MOCKS_INFRASTRUCTURE_CONFIGURATION_MANAGER_MOCK_HPP_
#define INCLUDED_MOCKS_INFRASTRUCTURE_CONFIGURATION_MANAGER_MOCK_HPP_

#include <Infrastructure/Interfaces/IConfigurationManager.hpp>

namespace inf {

	class ConfigurationManagerMock : public IConfigurationManager {
	public:
		~ConfigurationManagerMock(void) override {
			
		}
		void loadCustomConfigurations(LuaManager& _luaManager) override {
			
		}
		sf::Vector2u getResolution(void) const override {
			return resolution;
		}
		float getGameViewScale(void) const override {
			return scale;
		}
		std::string getTitle(void) const override {
			return title;
		}

		float scale{1.0f};
		sf::Vector2u resolution;
		std::string title;
	};

}

#endif // INCLUDED_MOCKS_INFRASTRUCTURE_CONFIGURATION_MANAGER_MOCK_HPP_