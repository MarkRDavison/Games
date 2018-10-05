#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_WORKER_RECRUITMENT_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_WORKER_RECRUITMENT_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IWorkerRecruitmentService.hpp>
#include <functional>

namespace drl {
	
	class WorkerRecruitmentServiceMock : public IWorkerRecruitmentService {
	public:
		~WorkerRecruitmentServiceMock(void) override {}

		void recruitWorkers(const ShuttleInstance& _shuttle) override {
			if (recruitWorkersCallback) {
				recruitWorkersCallback(_shuttle);
			}
		}

		std::function<void(const ShuttleInstance&)> recruitWorkersCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_WORKER_RECRUITMENT_SERVICE_MOCK_HPP_