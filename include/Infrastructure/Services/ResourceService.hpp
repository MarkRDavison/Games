#ifndef INCLUDED_INFRASTRUCTURE_SERVICES_RESOURCE_SERVICE_HPP_
#define INCLUDED_INFRASTRUCTURE_SERVICES_RESOURCE_SERVICE_HPP_

#include <Infrastructure/Services/Interfaces/IResourceService.hpp>
#include <map>

namespace inf {
	
	class ResourceService : public IResourceService {
	protected:
		struct LevelResource {
			std::string name;
			int amount{ 0 };
			int max{ DefaultResourceMaximum };
		};
	public:
		~ResourceService(void) override;

		void updateResource(const std::string& _resourceName, int _amount) override;
		void setResource(const std::string& _resourceName, int _amount) override;
		void setResourceMaximum(const std::string& _resourceName, int _maximum) override;
		int getResource(const std::string& _resourceName) override;
		bool canAfford(const ResourceBundle& _resourceBundle) override;
		void payResourceBundle(const ResourceBundle& _resourceBundle) override;
		void receiveResourceBundle(const ResourceBundle& _resourceBundle) override;
	protected:
		bool resourceExists(const std::string& _resourceName) const;
		LevelResource&  getOrCreateResource(const std::string& _resourceName);
		static void revalidateResourceAgainstMaximum(LevelResource& _resource);

	private:
		std::map<std::string, LevelResource> m_ResourceMap;
	};

}

#endif // INCLUDED_INFRASTRUCTURE_SERVICES_RESOURCE_SERVICE_HPP_