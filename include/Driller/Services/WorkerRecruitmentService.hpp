#ifndef INCLUDED_DRILLER_SERVICES_WORKER_RECRUITMENT_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_WORKER_RECRUITMENT_SERVICE_HPP_

#include <Driller/Services/Interfaces/IWorkerRecruitmentService.hpp>
#include <Driller/Services/Interfaces/IWorkerCreationService.hpp>
#include "Interfaces/IShuttleDepartureService.hpp"

namespace drl {
	class WorkerRecruitmentService : public IWorkerRecruitmentService {
	public:
		WorkerRecruitmentService(IWorkerCreationService& _workerCreationService, IShuttleDepartureService& _shuttleDepartureService);
		~WorkerRecruitmentService(void) override;

		void recruitWorkers(const ShuttleInstance& _shuttle) override;

	private:
		IWorkerCreationService& m_WorkerCreationService;
		IShuttleDepartureService& m_ShuttleDepartureService;
	};
}

#endif // INCLUDED_DRILLER_SERVICES_WORKER_RECRUITMENT_SERVICE_HPP_