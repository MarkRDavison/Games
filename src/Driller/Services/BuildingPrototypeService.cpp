#include <Driller/Services/BuildingPrototypeService.hpp>

namespace drl {

	BuildingPrototypeService::BuildingPrototypeService(IIdentificationService& _identificationService) :
		PrototypeService<BuildingPrototype, BuildingInstance, BuildingPrototypeId>(_identificationService) {

	}
	
	BuildingPrototypeService::~BuildingPrototypeService(void) {
		
	}


	BuildingInstance BuildingPrototypeService::createInstance(const BuildingPrototypeId& _prototypeId) {
		if (isPrototypeRegistered(_prototypeId)) {
			const BuildingPrototype& p = getPrototype(_prototypeId);
			BuildingInstance building{};
			building.Id = m_IdentificationService.generateId();
			building.size = p.size;
			building.textureCoords = p.textureCoords;
			building.providedWorkerPrototypeId = p.providedWorkerPrototypeId;
			building.providedWorkerPrototypeAmount = p.providedWorkerPrototypeAmount;
			building.providesNeeds = p.providesNeeds;
			building.providedNeeds = p.providedNeeds;
			building.providedNeedId = p.providedNeedId;
			building.providedNeedRate = p.providedNeedRate;
			return building;
		}
		return BuildingInstance{};
	}
}