#include <Driller/Services/WorkerPrototypeService.hpp>

namespace drl {

	WorkerPrototypeService::WorkerPrototypeService(IIdentificationService& _identificationService) :
		PrototypeService<WorkerPrototype, WorkerInstance, WorkerPrototypeId>(_identificationService) {

	}

	WorkerPrototypeService::~WorkerPrototypeService(void) {

	}

	WorkerInstance WorkerPrototypeService::createInstance(const WorkerPrototypeId& _prototypeId) {
		const WorkerPrototype& p = getPrototype(_prototypeId);
		WorkerInstance instance{};
		instance.Id = m_IdentificationService.generateId();
		instance.validJobTypes = p.validJobTypes;
		return instance;
	}

}
