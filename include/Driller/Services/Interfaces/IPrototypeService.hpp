#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_PROTOTYPE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_PROTOTYPE_SERVICE_HPP_

#include <string>
#include <Driller/DataStructures/BuildingPrototype.hpp>
#include <Driller/DataStructures/BuildingInstance.hpp>
#include <Driller/DataStructures/JobPrototype.hpp>
#include <Driller/DataStructures/JobInstance.hpp>
#include <Driller/DataStructures/WorkerPrototype.hpp>
#include <Driller/DataStructures/WorkerInstance.hpp>
#include <Driller/DataStructures/ShuttlePrototype.hpp>
#include <Driller/DataStructures/ShuttleInstance.hpp>

namespace drl {
	template <typename TPrototype, typename TInstance, typename TPrototypeId>
	class IPrototypeService {
	public:
		virtual ~IPrototypeService(void) = 0;

		virtual TPrototypeId getPrototypeId(const std::string& _prototypeName) const = 0;

		virtual void registerPrototype(const std::string& _prototypeName, const TPrototype& _prototype) = 0;
		virtual void registerPrototype(const TPrototypeId& _prototypeId, const TPrototype& _prototype) = 0;

		virtual const TPrototype& getPrototype(const std::string& _prototypeName) = 0;
		virtual const TPrototype& getPrototype(const TPrototypeId& _prototypeId) = 0;

		virtual TInstance createInstance(const std::string& _prototypeName) = 0;
		virtual TInstance createInstance(const TPrototypeId& _prototypeId) = 0;

		virtual bool isPrototypeRegistered(const std::string& _prototypeName) const = 0;
		virtual bool isPrototypeRegistered(const TPrototypeId& _prototypeId) const = 0;
	};
	
	using IBuildingPrototypeService = IPrototypeService<BuildingPrototype, BuildingInstance, BuildingPrototypeId>;
	inline IPrototypeService<BuildingPrototype, BuildingInstance, BuildingPrototypeId>::~IPrototypeService<BuildingPrototype, BuildingInstance, BuildingPrototypeId>(void) = default;

	using IJobPrototypeService = IPrototypeService<JobPrototype, JobInstance, JobPrototypeId>;
	inline IPrototypeService<JobPrototype, JobInstance, JobPrototypeId>::~IPrototypeService<JobPrototype, JobInstance, JobPrototypeId>(void) = default;

	using IShuttlePrototypeService = IPrototypeService<ShuttlePrototype, ShuttleInstance, ShuttlePrototypeId>;
	inline IPrototypeService<ShuttlePrototype, ShuttleInstance, ShuttlePrototypeId>::~IPrototypeService<ShuttlePrototype, ShuttleInstance, ShuttlePrototypeId>(void) = default;

	using IWorkerPrototypeService = IPrototypeService<WorkerPrototype, WorkerInstance, WorkerPrototypeId>;
	inline IPrototypeService<WorkerPrototype, WorkerInstance, WorkerPrototypeId>::~IPrototypeService<WorkerPrototype, WorkerInstance, WorkerPrototypeId>(void) = default;
}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_PROTOTYPE_SERVICE_HPP_