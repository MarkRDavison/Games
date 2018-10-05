#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_CREATION_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_CREATION_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IShuttleCreationService.hpp>
#include <functional>

namespace drl {
	
	class ShuttleCreationServiceMock : public IShuttleCreationService {
	public:
		~ShuttleCreationServiceMock(void) override {}

		bool canCreateShuttle(const GameCommand::CreateShuttleEvent& _event) override {
			if (canCreateShuttleCallback) {
				return canCreateShuttleCallback(_event);
			}
			return false;
		}
		void createShuttle(const GameCommand::CreateShuttleEvent& _event) override {
			if (createShuttleCallback) {
				createShuttleCallback(_event);
			}
		}

		std::function<bool(const GameCommand::CreateShuttleEvent&)> canCreateShuttleCallback;
		std::function<void(const GameCommand::CreateShuttleEvent&)> createShuttleCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_CREATION_SERVICE_MOCK_HPP_