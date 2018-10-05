#include <Driller/Services/WorkerRecruitmentService.hpp>

namespace drl {

	WorkerRecruitmentService::WorkerRecruitmentService(IWorkerCreationService& _workerCreationService, IShuttleDepartureService& _shuttleDepartureService) :
		m_WorkerCreationService(_workerCreationService),
		m_ShuttleDepartureService(_shuttleDepartureService) {
		
	}
	WorkerRecruitmentService::~WorkerRecruitmentService(void) {
		
	}

	void WorkerRecruitmentService::recruitWorkers(const ShuttleInstance& _shuttle) {
		int workersRecruited = 0;
		int workerFailedRecruit = 0;

		while (workersRecruited < _shuttle.capacity) {
			if (m_ShuttleDepartureService.workerPrototypeQueueEmpty(workerFailedRecruit)) {
				return;
			}

			GameCommand::CreateWorkerEvent event{};
			event.prototypeId = m_ShuttleDepartureService.peekWorkerPrototypeQueue(workerFailedRecruit);
			event.position = _shuttle.position;

			if (m_WorkerCreationService.canCreateWorker(event)) {
				m_WorkerCreationService.createWorker(event);
				workersRecruited++;
			} else {
				workerFailedRecruit++;
			}
		}
	}

}