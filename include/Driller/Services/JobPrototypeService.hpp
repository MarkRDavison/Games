#ifndef INCLUDED_DRILLER_SERVICES_JOB_PROTOTYPE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_JOB_PROTOTYPE_SERVICE_HPP_

#include <Driller/DataStructures/JobInstance.hpp>
#include <Driller/DataStructures/JobPrototype.hpp>
#include <Driller/Services/PrototypeService.hpp>

namespace drl {
	
	class JobPrototypeService : public PrototypeService<JobPrototype, JobInstance, JobPrototypeId> {
	public:
		explicit JobPrototypeService(IIdentificationService& _identificationService);
		~JobPrototypeService(void) override;

		JobInstance createInstance(const JobPrototypeId& _prototypeId) override;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_JOB_PROTOTYPE_SERVICE_HPP_