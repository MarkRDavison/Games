#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_WORKER_CREATION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_WORKER_CREATION_SERVICE_HPP_

#include <Driller/DataStructures/GameCommand.hpp>

namespace drl {
	
	class IWorkerCreationService {
	public:
		virtual ~IWorkerCreationService(void) = 0;

		virtual bool canCreateWorker(const GameCommand::CreateWorkerEvent& _event) = 0;
		virtual void createWorker(const GameCommand::CreateWorkerEvent& _event) = 0;
	};

	inline IWorkerCreationService::~IWorkerCreationService(void) = default;

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_WORKER_CREATION_SERVICE_HPP_