#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_PROTOTYPE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_PROTOTYPE_SERVICE_HPP_

#include <string>
#include <Driller/DataStructures/BuildingPrototype.hpp>
#include <Driller/DataStructures/BuildingInstance.hpp>
#include <Driller/DataStructures/JobPrototype.hpp>
#include <Driller/DataStructures/JobInstance.hpp>
#include <Driller/DataStructures/WorkerPrototype.hpp>
#include <Driller/DataStructures/WorkerInstance.hpp>

namespace drl {
	template <typename TPrototype, typename TInstance, typename TPrototypeId>
	class IPrototypeService {
	public:
		virtual ~IPrototypeService(void) = 0 {}

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
	using IJobPrototypeService = IPrototypeService<JobPrototype, JobInstance, JobPrototypeId>;
	using IWorkerPrototypeService = IPrototypeService<WorkerPrototype, WorkerInstance, WorkerPrototypeId>;
}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_PROTOTYPE_SERVICE_HPP_