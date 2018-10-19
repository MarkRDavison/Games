#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_CARGO_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_CARGO_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IShuttleCargoService.hpp>
#include <Utility/TestSignal.hpp>

namespace drl {
	
	class ShuttleCargoServiceMock : public IShuttleCargoService {
	public:
		~ShuttleCargoServiceMock(void) {}

		void loadShuttleWithCargo(ShuttleInstance& _shuttle) override {
			loadShuttleWithCargoCallback(_shuttle);
		}

		inf::TestSignal<void, ShuttleInstance&> loadShuttleWithCargoCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_CARGO_SERVICE_MOCK_HPP_