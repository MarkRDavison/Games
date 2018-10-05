#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_UPDATE_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_UPDATE_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IShuttleUpdateService.hpp>
#include <functional>

namespace drl {

	class ShuttleUpdateServiceMock : public IShuttleUpdateService {
	public:
		~ShuttleUpdateServiceMock(void) override {}

		void update(float _delta) override {
			if (updateCallback) {
				updateCallback(_delta);
			}
		}

		std::function<void(float)> updateCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_UPDATE_SERVICE_MOCK_HPP_