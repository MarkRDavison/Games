#include <Driller/Services/WorkerCreationService.hpp>

namespace drl {

	WorkerCreationService::WorkerCreationService(WorkerData& _workerData, IWorkerPrototypeService& _prototypeService) :
		m_WorkerData(_workerData),
		m_PrototypeService(_prototypeService) {
		
	}

	WorkerCreationService::~WorkerCreationService(void) {
		
	}

	bool WorkerCreationService::canCreateWorker(const GameCommand::CreateWorkerEvent& _event) {
		return m_PrototypeService.isPrototypeRegistered(_event.prototypeId);
	}

	void WorkerCreationService::createWorker(const GameCommand::CreateWorkerEvent& _event) {
		WorkerInstance& instance = m_WorkerData.workers.emplace_back(m_PrototypeService.createInstance(_event.prototypeId));
		instance.position = _event.position;
	}

}