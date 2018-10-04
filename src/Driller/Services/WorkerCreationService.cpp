#include <Driller/Services/WorkerCreationService.hpp>

namespace drl {

	WorkerCreationService::WorkerCreationService(WorkerData& _workerData, IWorkerPrototypeService& _prototypeService, IWorkerClassService& _workerClassService) :
		m_WorkerData(_workerData),
		m_PrototypeService(_prototypeService),
		m_WorkerClassService(_workerClassService) {
		
	}

	WorkerCreationService::~WorkerCreationService(void) {
		
	}

	bool WorkerCreationService::canCreateWorker(const GameCommand::CreateWorkerEvent& _event) {
		return 
			m_PrototypeService.isPrototypeRegistered(_event.prototypeId) && 
			m_WorkerClassService.canIncreaseClass(_event.prototypeId, 1) &&
			m_WorkerClassService.canIncreaseClass(inf::djb_hash(Definitions::CurrentWorkerResourceName), 1); // TODO: make this better
	}

	void WorkerCreationService::createWorker(const GameCommand::CreateWorkerEvent& _event) {
		m_WorkerClassService.increaseClass(inf::djb_hash(Definitions::CurrentWorkerResourceName), 1); // TODO: Make this better?
		m_WorkerClassService.increaseClass(_event.prototypeId, 1);
		WorkerInstance& instance = m_WorkerData.workers.emplace_back(m_PrototypeService.createInstance(_event.prototypeId));
		instance.position = _event.position;
	}

}