#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_IDENTIFICATION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_IDENTIFICATION_SERVICE_HPP_

#include <Driller/Infrastructure/Definitions.hpp>

namespace drl {
	
	class IIdentificationService {
	public:
		virtual ~IIdentificationService(void) = 0 {}

		virtual EntityId generateId(void) = 0;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_IDENTIFICATION_SERVICE_HPP_