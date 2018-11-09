#ifndef INCLUDED_INFRASTRUCTURE_SERVICES_INTERFACES_I_RESOURCE_SERVICE_HPP_
#define INCLUDED_INFRASTRUCTURE_SERVICES_INTERFACES_I_RESOURCE_SERVICE_HPP_

#include <string>
#include <Utility/Signal.hpp>
#include <Infrastructure/DataStructures/ResourceBundle.hpp>

namespace inf {
	
	class IResourceService {
	public:
		virtual ~IResourceService(void) = 0;

		virtual void updateResource(const std::string& _resourceName, int _amount) = 0;
		virtual void updateResourceMax(const std::string& _resourceName, int _amount) = 0;
		virtual void setResource(const std::string& _resourceName, int _amount) = 0;
		virtual void setResourceMaximum(const std::string& _resourceName, int _maximum) = 0;
		virtual int getResource(const std::string& _resourceName) = 0;
		virtual int getResourceMax(const std::string& _resourceName) = 0;
		virtual bool canAfford(const ResourceBundle& _resourceBundle) = 0;
		virtual bool canAfford(std::size_t _resourceId, int _amount) = 0;
		virtual void payResourceBundle(const ResourceBundle& _resourceBundle) = 0;
		virtual void payResourceId(std::size_t _resourceId, int _amount) = 0;
		virtual void receiveResourceBundle(const ResourceBundle& _resourceBundle) = 0;
		virtual void receiveResourceMaxBundle(const ResourceBundle& _resourceBundle) = 0;
		virtual void registerResourceId(const std::string& _resourceName) = 0;

		Signal<const std::string&> resourceChanged;

		static constexpr const int DefaultResourceMaximum = -1;
	};

	inline IResourceService::~IResourceService(void) = default;

}

#endif // INCLUDED_INFRASTRUCTURE_SERVICES_INTERFACES_I_RESOURCE_SERVICE_HPP_