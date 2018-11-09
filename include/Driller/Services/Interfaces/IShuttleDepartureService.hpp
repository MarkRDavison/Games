#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_SHUTTLE_DEPARTURE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_SHUTTLE_DEPARTURE_SERVICE_HPP_

#include <Driller/DataStructures/ShuttlePrototype.hpp>
#include <Driller/DataStructures/WorkerPrototype.hpp>

namespace drl {
	
	class IShuttleDepartureService {
	public:
		virtual ~IShuttleDepartureService(void) = 0;

		virtual void update(float _delta) = 0;

		virtual void registerShuttle(const ShuttlePrototypeId& _prototypeId, float _departureInterval) = 0;
		virtual ShuttlePrototypeId getCurrentPrototypeId(void) const = 0;
		virtual float getCurrentDepartureInterval(void) const = 0;

		virtual void addWorkerPrototypeToQueue(const WorkerPrototypeId& _workerPrototypeId) = 0;
		virtual WorkerPrototypeId peekWorkerPrototypeQueue(int _failedPeeks) const = 0;
		virtual void popWorkerPrototoypeQueue(int _failedPeeks) = 0;
		virtual bool workerPrototypeQueueEmpty(int _failedPeeks) const = 0;

		virtual void setShuttleOnRun(bool _onRun) = 0;
		virtual bool getShuttleOnRun(void) const = 0;
	};

	inline IShuttleDepartureService::~IShuttleDepartureService(void) = default;

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_SHUTTLE_DEPARTURE_SERVICE_HPP_