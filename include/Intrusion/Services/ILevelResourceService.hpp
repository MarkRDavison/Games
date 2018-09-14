#ifndef INCLUDED_INTRUSION_SERVICES_I_LEVEL_RESOURCE_SERVICE_HPP_
#define INCLUDED_INTRUSION_SERVICES_I_LEVEL_RESOURCE_SERVICE_HPP_

#include <string>
#include <functional>

#include <Intrusion/DataStructures/ResourceBundle.hpp>

namespace itr {
	
	class ILevelResourceService {
	public:
		virtual ~ILevelResourceService(void) = default;

		virtual void updateResource(const std::string& _resourceName, int _amount) = 0;
		virtual void setResource(const std::string& _resourceName, int _amount) = 0;
		virtual void setResourceMaximum(const std::string& _resourceName, int _maximum) = 0;
		virtual int getResource(const std::string& _resourceName) = 0;
		virtual bool canAfford(const ResourceBundle& _resourceBundle) = 0;

		std::function<void(std::string)> resourceChanged;
	};

}

#endif // INCLUDED_INTRUSION_SERVICES_I_LEVEL_RESOURCE_SERVICE_HPP_