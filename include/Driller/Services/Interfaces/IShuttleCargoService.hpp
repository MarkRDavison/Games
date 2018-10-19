#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_SHUTTLE_CARGO_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_SHUTTLE_CARGO_SERVICE_HPP_

#include <Driller/DataStructures/ShuttleInstance.hpp>

namespace drl {
	
	class IShuttleCargoService {
	protected:
		virtual ~IShuttleCargoService(void) = 0 {}

	public:
		virtual void loadShuttleWithCargo(ShuttleInstance& _shuttle) = 0;

	};

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_SHUTTLE_CARGO_SERVICE_HPP_