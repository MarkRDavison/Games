#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_DEPARTURE_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_DEPARTURE_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IShuttleDepartureService.hpp>
#include <functional>

namespace drl {
	
	class ShuttleDepartureServiceMock : public IShuttleDepartureService {
	public:
		~ShuttleDepartureServiceMock(void) override {}

		void update(float _delta) override {
			if (updateCallback) {
				updateCallback(_delta);
			}
		}

		void registerShuttle(const ShuttlePrototypeId& _prototypeId, float _departureInterval) override {
			if (registerShuttleCallback) {
				registerShuttleCallback(_prototypeId, _departureInterval);
			}
		}

		ShuttlePrototypeId getCurrentPrototypeId(void) const override {
			if (getCurrentPrototypeIdCallback) {
				return getCurrentPrototypeIdCallback();
			}

			return 0u;
		}
		float getCurrentDepartureInterval(void) const override {
			if (getCurrentDepartureIntervalCallback) {
				return getCurrentDepartureIntervalCallback();
			}

			return 0.0f;
		}

		void addWorkerPrototypeToQueue(const WorkerPrototypeId& _workerPrototypeId) override {
			if (addWorkerPrototypeToQueueCallback) {
				addWorkerPrototypeToQueueCallback(_workerPrototypeId);
			}
		}
		WorkerPrototypeId peekWorkerPrototypeQueue(int _failedPeeks) const override {
			if (peekWorkerPrototypeQueueCallback) {
				return peekWorkerPrototypeQueueCallback(_failedPeeks);
			}
			return {};
		}
		void popWorkerPrototoypeQueue(int _failedPeeks) override {
			if (popWorkerPrototoypeQueueCallback) {
				popWorkerPrototoypeQueueCallback(_failedPeeks);
			}
		}
		bool workerPrototypeQueueEmpty(int _failedPeeks) const override {
			if (workerPrototypeQueueEmptyCallback) {
				return workerPrototypeQueueEmptyCallback(_failedPeeks);
			}
			return false;
		}

		void setShuttleOnRun(bool _onRun) override {
			if (setShuttleOnRunCallback) {
				setShuttleOnRunCallback(_onRun);
			}
		}
		bool getShuttleOnRun(void) const override {
			if (getShuttleOnRunCallback) {
				return getShuttleOnRunCallback();
			}

			return true;
		}

		std::function<void(float)> updateCallback;
		std::function<void(const ShuttlePrototypeId&, float)> registerShuttleCallback;
		std::function<ShuttlePrototypeId(void)> getCurrentPrototypeIdCallback;
		std::function<float(void)> getCurrentDepartureIntervalCallback;
		std::function<void(const WorkerPrototypeId&)> addWorkerPrototypeToQueueCallback;
		std::function<WorkerPrototypeId(int)> peekWorkerPrototypeQueueCallback;
		std::function<void(int)> popWorkerPrototoypeQueueCallback;
		std::function<bool(int)> workerPrototypeQueueEmptyCallback;
		std::function<void(bool)> setShuttleOnRunCallback;
		std::function<bool(void)> getShuttleOnRunCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_SHUTTLE_DEPARTURE_SERVICE_MOCK_HPP_