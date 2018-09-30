#include <Driller/Services/JobPrototypeService.hpp>

namespace drl {

	JobPrototypeService::JobPrototypeService(IIdentificationService& _identificationService) :
		PrototypeService<JobPrototype, JobInstance, JobPrototypeId>(_identificationService) {

	}

	JobPrototypeService::~JobPrototypeService(void) {
		
	}

	JobInstance JobPrototypeService::createInstance(const JobPrototypeId& _prototypeId) {
		JobInstance instance{};
		instance.Id = m_IdentificationService.generateId();
		return instance;
	}

}
