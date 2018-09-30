#ifndef INCLUDED_DRILLER_SERVICES_BUILDING_PROTOTYPE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_BUILDING_PROTOTYPE_SERVICE_HPP_

#include <Driller/DataStructures/BuildingInstance.hpp>
#include <Driller/DataStructures/BuildingPrototype.hpp>
#include <Driller/Services/PrototypeService.hpp>

namespace drl {

	class BuildingPrototypeService : public PrototypeService<BuildingPrototype, BuildingInstance, BuildingPrototypeId> {
	public:
		explicit BuildingPrototypeService(IIdentificationService& _identificationService);
		~BuildingPrototypeService(void) override;

		BuildingInstance createInstance(const BuildingPrototypeId& _prototypeId) override;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_BUILDING_PROTOTYPE_SERVICE_HPP_