#ifndef INCLUDED_DRILLER_SERVICES_SHUTTLE_PROTOTYPE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_SHUTTLE_PROTOTYPE_SERVICE_HPP_

#include <Driller/DataStructures/ShuttleInstance.hpp>
#include <Driller/DataStructures/ShuttlePrototype.hpp>
#include <Driller/Services/PrototypeService.hpp>

namespace drl {

	class ShuttlePrototypeService : public PrototypeService<ShuttlePrototype, ShuttleInstance, ShuttlePrototypeId> {
	public:
		explicit ShuttlePrototypeService(IIdentificationService& _identificationService);
		~ShuttlePrototypeService(void) override;

		ShuttleInstance createInstance(const ShuttlePrototypeId& _prototypeId) override;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_SHUTTLE_PROTOTYPE_SERVICE_HPP_