#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_WORKER_CLASS_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_WORKER_CLASS_SERVICE_HPP_

#include <Driller/DataStructures/WorkerPrototype.hpp>

namespace drl {
	
	class IWorkerClassService {
	public:
		virtual ~IWorkerClassService(void) = 0;

		virtual void registerPrototypeToResourceClass(const WorkerPrototypeId& _prototypeId, const std::string& _resource) = 0;
		virtual bool isPrototypeRegistered(const WorkerPrototypeId& _prototypeId) = 0;

		virtual void increaseClassMaximum(const WorkerPrototypeId& _prototypeId, int _amount) = 0;
		virtual void increaseClass(const WorkerPrototypeId& _prototypeId, int _amount) = 0;
		virtual bool canIncreaseClass(const WorkerPrototypeId& _prototypeId, int _amount) = 0;

		virtual void decreaseClassMaximum(const WorkerPrototypeId& _prototypeId, int _amount) = 0;
		virtual void decreaseClass(const WorkerPrototypeId& _prototypeId, int _amount) = 0;
	};

	inline IWorkerClassService::~IWorkerClassService(void) = default;

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_WORKER_CLASS_SERVICE_HPP_