#ifndef INCLUDED_DRILLER_SERVICES_WORKER_PROTOTYPE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_WORKER_PROTOTYPE_SERVICE_HPP_

#include <Driller/DataStructures/WorkerInstance.hpp>
#include <Driller/DataStructures/WorkerPrototype.hpp>
#include <Driller/Services/PrototypeService.hpp>

namespace drl {

	class WorkerPrototypeService : public PrototypeService<WorkerPrototype, WorkerInstance, WorkerPrototypeId> {
	public:
		explicit WorkerPrototypeService(IIdentificationService& _identificationService);
		~WorkerPrototypeService(void) override;

		WorkerInstance createInstance(const WorkerPrototypeId& _prototypeId) override;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_WORKER_PROTOTYPE_SERVICE_HPP_