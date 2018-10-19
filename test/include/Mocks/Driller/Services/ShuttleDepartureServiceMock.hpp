#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_DEPARTURE_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_DEPARTURE_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IShuttleDepartureService.hpp>
#include <Utility/TestSignal.hpp>

namespace drl {
	
	class ShuttleDepartureServiceMock : public IShuttleDepartureService {
	public:
		~ShuttleDepartureServiceMock(void) override {}

		void update(float _delta) override {
			updateCallback(_delta);
		}

		void registerShuttle(const ShuttlePrototypeId& _prototypeId, float _departureInterval) override {
			registerShuttleCallback(_prototypeId, _departureInterval);
		}

		ShuttlePrototypeId getCurrentPrototypeId(void) const override {
			return getCurrentPrototypeIdCallback.invoke();
		}
		float getCurrentDepartureInterval(void) const override {
			return getCurrentDepartureIntervalCallback.invoke();
		}

		void addWorkerPrototypeToQueue(const WorkerPrototypeId& _workerPrototypeId) override {
			addWorkerPrototypeToQueueCallback(_workerPrototypeId);
		}
		WorkerPrototypeId peekWorkerPrototypeQueue(int _failedPeeks) const override {
			return peekWorkerPrototypeQueueCallback(_failedPeeks);
		}
		void popWorkerPrototoypeQueue(int _failedPeeks) override {
			popWorkerPrototoypeQueueCallback(_failedPeeks);			
		}
		bool workerPrototypeQueueEmpty(int _failedPeeks) const override {
			return workerPrototypeQueueEmptyCallback(_failedPeeks);
		}

		void setShuttleOnRun(bool _onRun) override {
			setShuttleOnRunCallback(_onRun);
		}
		bool getShuttleOnRun(void) const override {
			return getShuttleOnRunCallback.invoke();
		}

		inf::TestSignal<void, float> updateCallback;
		inf::TestSignal<void, const ShuttlePrototypeId&, float> registerShuttleCallback;
		inf::TestSignal<ShuttlePrototypeId> getCurrentPrototypeIdCallback;
		inf::TestSignal<float> getCurrentDepartureIntervalCallback;
		inf::TestSignal<void, const WorkerPrototypeId&> addWorkerPrototypeToQueueCallback;
		inf::TestSignal<WorkerPrototypeId, int> peekWorkerPrototypeQueueCallback;
		inf::TestSignal<void, int> popWorkerPrototoypeQueueCallback;
		inf::TestSignal<bool, int> workerPrototypeQueueEmptyCallback;
		inf::TestSignal<void, bool> setShuttleOnRunCallback;
		inf::TestSignal<bool> getShuttleOnRunCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_DEPARTURE_SERVICE_MOCK_HPP_