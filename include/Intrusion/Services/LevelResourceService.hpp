#ifndef INCLUDED_INTRUSION_SERVICES_LEVEL_RESOURCE_SERVICE_HPP_
#define INCLUDED_INTRUSION_SERVICES_LEVEL_RESOURCE_SERVICE_HPP_

#include <Intrusion/Infrastructure/IntrusionDefinitions.hpp>
#include <Intrusion/Services/ILevelResourceService.hpp>

#include <map>

namespace itr {
	class LevelResourceService : public ILevelResourceService {
	protected:
		struct LevelResource {
			std::string name;
			int amount{0};
			int max{ Definitions::DefaultResourceMaximum };
		};
	public:
		LevelResourceService(void);
		~LevelResourceService(void) override;

		void updateResource(const std::string& _resourceName, int _amount) override;
		void setResource(const std::string& _resourceName, int _amount) override;
		void setResourceMaximum(const std::string& _resourceName, int _maximum) override;
		int getResource(const std::string& _resourceName) override; 
		bool canAfford(const ResourceBundle& _resourceBundle) override;

	protected:
		bool resourceExists(const std::string& _resourceName) const;
		LevelResourceService::LevelResource&  LevelResourceService::getOrCreateResource(const std::string& _resourceName);
		static void revalidateResourceAgainstMaximum(LevelResource& _resource);

	private:
		std::map<std::string, LevelResource> m_ResourceMap;
	};
}

#endif // INCLUDED_INTRUSION_SERVICES_LEVEL_RESOURCE_SERVICE_HPP_