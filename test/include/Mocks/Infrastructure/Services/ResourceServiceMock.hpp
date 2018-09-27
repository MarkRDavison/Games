#ifndef INCLUDED_MOCKS_INFRASTRUCTURE_SERVICES_RESOURCE_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_INFRASTRUCTURE_SERVICES_RESOURCE_SERVICE_MOCK_HPP_

#include <Infrastructure/Services/Interfaces/IResourceService.hpp>

namespace inf {
	class ResourceServiceMock : public inf::IResourceService {
	public:
		~ResourceServiceMock(void) override {}

		void updateResource(const std::string& _resourceName, int _amount) override {
			if (updateResourceCallback) {
				updateResourceCallback(_resourceName, _amount);
			}
		}
		void setResource(const std::string& _resourceName, int _amount) override {
			if (setResourceCallback) {
				setResourceCallback(_resourceName, _amount);
			}
		}
		void setResourceMaximum(const std::string& _resourceName, int _maximum) override {
			if (setResourceMaximumCallback) {
				setResourceMaximumCallback(_resourceName, _maximum);
			}
		}
		int getResource(const std::string& _resourceName) override {
			if (getResourceCallback) {
				return getResourceCallback(_resourceName);
			}

			return 0;
		}
		bool canAfford(const ResourceBundle& _resourceBundle) override {
			if (canAffordCallback) {
				return canAffordCallback(_resourceBundle);
			}

			return false;
		}
		void payResourceBundle(const ResourceBundle& _resourceBundle) override {
			if (payResourceBundleCallback) {
				payResourceBundleCallback(_resourceBundle);
			}
		}
		void receiveResourceBundle(const ResourceBundle& _resourceBundle) override {
			if (receiveResourceBundleCallback) {
				receiveResourceBundleCallback(_resourceBundle);
			}
		}

		std::function<void(const std::string&, int)> updateResourceCallback;
		std::function<void(const std::string&, int)> setResourceCallback;
		std::function<void(const std::string&, int)> setResourceMaximumCallback;
		std::function<int(const std::string&)> getResourceCallback;
		std::function<bool(const ResourceBundle&)> canAffordCallback;
		std::function<void(const ResourceBundle&)> payResourceBundleCallback;
		std::function<void(const ResourceBundle&)> receiveResourceBundleCallback;
	};
}

#endif // INCLUDED_MOCKS_INTRUSION_SERVICES_LEVEL_RESOURCE_SERVICE_MOCK_HPP_