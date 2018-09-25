#include <Infrastructure/Services/ResourceService.hpp>

namespace inf {
	
	ResourceService::~ResourceService(void) {

	}

	void ResourceService::updateResource(const std::string& _resourceName, int _amount) {
		setResource(_resourceName, _amount + getResource(_resourceName));
	}

	void ResourceService::setResource(const std::string& _resourceName, int _amount) {
		LevelResource& resource = getOrCreateResource(_resourceName);
		resource.amount = _amount;
		revalidateResourceAgainstMaximum(resource);
		resourceChanged.invoke(_resourceName);
	}
	void ResourceService::setResourceMaximum(const std::string& _resourceName, int _maximum) {
		LevelResource& resource = getOrCreateResource(_resourceName);
		resource.max = _maximum;
		revalidateResourceAgainstMaximum(resource);
		resourceChanged.invoke(_resourceName);
	}
	int ResourceService::getResource(const std::string& _resourceName) {
		return getOrCreateResource(_resourceName).amount;
	}

	bool ResourceService::canAfford(const ResourceBundle& _resourceBundle) {

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

	void ResourceService::payResourceBundle(const ResourceBundle& _resourceBundle) {
		for (const ResourceBundle::Resource& _res : _resourceBundle.resources) {
			if (_res.amount == 0) {
				continue;
			}

			updateResource(_res.name, -_res.amount);
		}
	}

	void ResourceService::receiveResourceBundle(const ResourceBundle& _resourceBundle) {
		for (const ResourceBundle::Resource& _res : _resourceBundle.resources) {
			if (_res.amount == 0) {
				continue;
			}

			updateResource(_res.name, _res.amount);
		}
	}

	bool ResourceService::resourceExists(const std::string& _resourceName) const {
		return m_ResourceMap.find(_resourceName) != m_ResourceMap.end();
	}

	ResourceService::LevelResource&  ResourceService::getOrCreateResource(const std::string& _resourceName) {
		auto iter = m_ResourceMap.find(_resourceName);
		if (iter == m_ResourceMap.end()) {
			m_ResourceMap[_resourceName].name = _resourceName;
		}

		return m_ResourceMap[_resourceName];
	}

	void ResourceService::revalidateResourceAgainstMaximum(LevelResource& _resource) {
		if (_resource.amount > _resource.max && _resource.max != DefaultResourceMaximum) {
			_resource.amount = _resource.max;
		}
	}

}
