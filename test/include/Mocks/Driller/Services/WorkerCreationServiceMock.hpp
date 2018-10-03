#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_WORKER_CREATION_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_WORKER_CREATION_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IWorkerCreationService.hpp>
#include <functional>

namespace drl {
	
	class WorkerCreationServiceMock : public IWorkerCreationService {
	public:
		~WorkerCreationServiceMock(void) override {}

		bool canCreateWorker(const GameCommand::CreateWorkerEvent& _event) override {
			if (canCreateWorkerCallback) {
				return canCreateWorkerCallback(_event);
			}

			return false;
		}
		void createWorker(const GameCommand::CreateWorkerEvent& _event) override {
			if (createWorkerCallback) {
				createWorkerCallback(_event);
			}
		}

		std::function<bool(const GameCommand::CreateWorkerEvent&)> canCreateWorkerCallback;
		std::function<void(const GameCommand::CreateWorkerEvent&)> createWorkerCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_WORKER_CREATION_SERVICE_MOCK_HPP_