#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_COMPLETION_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_COMPLETION_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IShuttleCompletionService.hpp>
#include <functional>

namespace drl {
	
	class ShuttleCompletionServiceMock : public IShuttleCompletionService {
	public:
		~ShuttleCompletionServiceMock(void) override {}

		void handleShuttleCompleted(ShuttleInstance& _shuttle) override {
			if (handleShuttleCompletedCallback) {
				handleShuttleCompletedCallback(_shuttle);
			}
		}
		void cleanupCompletedShuttles(void) override {
			if (cleanupCompletedShuttlesCallback) {
				cleanupCompletedShuttlesCallback();
			}
		}

		std::function<void(ShuttleInstance&)> handleShuttleCompletedCallback;
		std::function<void(void)> cleanupCompletedShuttlesCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_COMPLETION_SERVICE_MOCK_HPP_