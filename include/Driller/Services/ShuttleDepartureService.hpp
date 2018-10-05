#ifndef INCLUDED_DRILLER_SERVICES_SHUTTLE_DEPARTURE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_SHUTTLE_DEPARTURE_SERVICE_HPP_

#include <Driller/Services/Interfaces/IShuttleDepartureService.hpp>
#include <Driller/Services/Interfaces/IShuttleCreationService.hpp>
#include <vector>

namespace drl {
	
	class ShuttleDepartureService : public IShuttleDepartureService {
	public:
		ShuttleDepartureService(IShuttleCreationService& _shuttleCreationService);
		~ShuttleDepartureService(void) override;

		void update(float _delta) override;

		void registerShuttle(const ShuttlePrototypeId& _prototypeId, float _departureInterval) override;
		ShuttlePrototypeId getCurrentPrototypeId(void) const override;
		float getCurrentDepartureInterval(void) const override;

		void addWorkerPrototypeToQueue(const WorkerPrototypeId& _workerPrototypeId) override;
		WorkerPrototypeId peekWorkerPrototypeQueue(int _failedPeeks) const override;
		void popWorkerPrototoypeQueue(int _failedPeeks) override;
		bool workerPrototypeQueueEmpty(int _failedPeeks) const override;

		void setShuttleOnRun(bool _onRun) override;
		bool getShuttleOnRun(void) const override;

	private:
		IShuttleCreationService& m_ShuttleCreationService;

		std::vector<WorkerPrototypeId> m_WorkersToCarry;
		ShuttlePrototypeId m_PrototypeId{0u};
		float m_DepartureInterval{0.0f};
		float m_AccumulatedTime{0.0f};
		bool m_OnRun{ false };
	};

}

#endif // INCLUDED_DRILLER_SERVICES_SHUTTLE_DEPARTURE_SERVICE_HPP_