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
		instance.prototypeId = _prototypeId;
		instance.workRequired = prototype.workRequired;
		instance.repeats = prototype.repeats;
		instance.Id = m_IdentificationService.generateId();
		return instance;
	}

}
