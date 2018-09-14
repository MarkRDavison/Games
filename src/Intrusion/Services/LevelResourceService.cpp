#include <Intrusion/Services/LevelResourceService.hpp>

namespace itr {

	LevelResourceService::LevelResourceService(void) {
		
	}
	LevelResourceService::~LevelResourceService(void) {
		
	}

	void LevelResourceService::updateResource(const std::string& _resourceName, int _amount) {
		setResource(_resourceName, _amount + getResource(_resourceName));
	}

	void LevelResourceService::setResource(const std::string& _resourceName, int _amount) {
		LevelResource& resource = getOrCreateResource(_resourceName);
		resource.amount = _amount;
		revalidateResourceAgainstMaximum(resource);
		if (resourceChanged) {
			resourceChanged(_resourceName);
		}
	}
	void LevelResourceService::setResourceMaximum(const std::string& _resourceName, int _maximum) {
		LevelResource& resource = getOrCreateResource(_resourceName);
		resource.max = _maximum;
		revalidateResourceAgainstMaximum(resource);
		if (resourceChanged) {
			resourceChanged(_resourceName);
		}
	}
	int LevelResourceService::getResource(const std::string& _resourceName) {
		return getOrCreateResource(_resourceName).amount;
	}

	bool LevelResourceService::canAfford(const ResourceBundle& _resourceBundle) {

		for (const ResourceBundle::Resource& _res : _resourceBundle.resources) {
			
			if (_res.amount == 0) {
				continue;
			}

			if (!resourceExists(_res.name)) {
				return false;
			}

			if (getResource(_res.name) < _res.amount) {
				return false;
			}

		}

		return true;
	}

	bool LevelResourceService::resourceExists(const std::string& _resourceName) const {
		return m_ResourceMap.find(_resourceName) != m_ResourceMap.end();
	}

	LevelResourceService::LevelResource&  LevelResourceService::getOrCreateResource(const std::string& _resourceName) {
		auto iter = m_ResourceMap.find(_resourceName);
		if (iter == m_ResourceMap.end()) {
			m_ResourceMap[_resourceName].name = _resourceName;
		}

		return m_ResourceMap[_resourceName];
	}

	void LevelResourceService::revalidateResourceAgainstMaximum(LevelResource& _resource) {
		if (_resource.amount > _resource.max && _resource.max != Definitions::DefaultResourceMaximum) {
			_resource.amount = _resource.max;
		}
	}
}
