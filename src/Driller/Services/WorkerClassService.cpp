#include <Driller/Services/WorkerClassService.hpp>
#include <cassert>

namespace drl {
	
	WorkerClassService::WorkerClassService(inf::IResourceService& _resourceService) :
		m_ResourceService(_resourceService) {
		
	}
	WorkerClassService::~WorkerClassService(void) {
		
	}

	void WorkerClassService::registerPrototypeToResourceClass(const WorkerPrototypeId& _prototypeId, const std::string& _resource) {
		if (!isPrototypeRegistered(_prototypeId)) {
			m_PrototypeResourceMap[_prototypeId] = _resource;
		}
	}
	bool WorkerClassService::isPrototypeRegistered(const WorkerPrototypeId& _prototypeId) {
		return m_PrototypeResourceMap.find(_prototypeId) != m_PrototypeResourceMap.end();
	}

	void WorkerClassService::increaseClassMaximum(const WorkerPrototypeId& _prototypeId, int _amount) {
		assert(isPrototypeRegistered(_prototypeId));
		m_ResourceService.updateResourceMax(m_PrototypeResourceMap[_prototypeId], _amount);
	}
	void WorkerClassService::increaseClass(const WorkerPrototypeId& _prototypeId, int _amount) {
		assert(isPrototypeRegistered(_prototypeId));
		m_ResourceService.updateResource(m_PrototypeResourceMap[_prototypeId], _amount);
	}
	bool WorkerClassService::canIncreaseClass(const WorkerPrototypeId& _prototypeId, int _amount) {
		assert(isPrototypeRegistered(_prototypeId));
		const auto& resource = m_PrototypeResourceMap[_prototypeId];
		return m_ResourceService.getResourceMax(resource) >= m_ResourceService.getResource(resource) + _amount;
	}

	void WorkerClassService::decreaseClassMaximum(const WorkerPrototypeId& _prototypeId, int _amount) {
		assert(isPrototypeRegistered(_prototypeId));
		m_ResourceService.updateResourceMax(m_PrototypeResourceMap[_prototypeId], -_amount);
	}
	void WorkerClassService::decreaseClass(const WorkerPrototypeId& _prototypeId, int _amount) {
		assert(isPrototypeRegistered(_prototypeId));
		m_ResourceService.updateResource(m_PrototypeResourceMap[_prototypeId], -_amount);
	}

}