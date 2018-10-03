#include <Driller/Services/JobPrototypeService.hpp>

namespace drl {

	JobPrototypeService::JobPrototypeService(IIdentificationService& _identificationService) :
		PrototypeService<JobPrototype, JobInstance, JobPrototypeId>(_identificationService) {

	}

	JobPrototypeService::~JobPrototypeService(void) {
		
	}

	JobInstance JobPrototypeService::createInstance(const JobPrototypeId& _prototypeId) {
		const JobPrototype& prototype = getPrototype(_prototypeId);
		JobInstance instance{};
		instance.workRequired = prototype.workRequired;
		instance.Id = m_IdentificationService.generateId();
		return instance;
	}

}
