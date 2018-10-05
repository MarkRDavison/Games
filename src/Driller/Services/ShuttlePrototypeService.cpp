#include <Driller/Services/ShuttlePrototypeService.hpp>

namespace drl {

	ShuttlePrototypeService::ShuttlePrototypeService(IIdentificationService& _identificationService) :
		PrototypeService<ShuttlePrototype, ShuttleInstance, ShuttlePrototypeId>(_identificationService) {
	}
	ShuttlePrototypeService::~ShuttlePrototypeService(void) {
		
	}

	ShuttleInstance ShuttlePrototypeService::createInstance(const ShuttlePrototypeId& _prototypeId) {
		const ShuttlePrototype& p = getPrototype(_prototypeId);
		ShuttleInstance instance{};
		instance.Id = m_IdentificationService.generateId();		
		instance.position = Definitions::ShuttleStartingCoordinates;
		instance.landingPosition = Definitions::ShuttleLandingCoordinates;
		instance.completePosition = Definitions::ShuttleEndingCoordinates;
		instance.loadingTime = p.loadingTime;
		instance.capacity = p.capacity;
		return instance;
	}

}