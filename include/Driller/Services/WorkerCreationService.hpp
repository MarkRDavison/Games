#ifndef INCLUDED_DRILLER_SERVICES_WORKER_CREATION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_WORKER_CREATION_SERVICE_HPP_

#include <Driller/Services/Interfaces/IWorkerCreationService.hpp>
#include <Driller/Services/Interfaces/IPrototypeService.hpp>
#include <Driller/DataStructures/WorkerData.hpp>

namespace drl {

	class WorkerCreationService : public IWorkerCreationService {
	public:
		WorkerCreationService(WorkerData& _workerData, IWorkerPrototypeService& _prototypeService);
		~WorkerCreationService(void) override;

		bool canCreateWorker(const GameCommand::CreateWorkerEvent& _event) override;
		void createWorker(const GameCommand::CreateWorkerEvent& _event) override;

	private:
		WorkerData& m_WorkerData;
		IWorkerPrototypeService& m_PrototypeService;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_WORKER_CREATION_SERVICE_HPP_