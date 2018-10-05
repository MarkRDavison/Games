#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_SHUTTLE_COMPLETION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_SHUTTLE_COMPLETION_SERVICE_HPP_

#include <Driller/DataStructures/ShuttleInstance.hpp>

namespace drl {
	
	class IShuttleCompletionService {
	public:
		virtual ~IShuttleCompletionService(void) = 0 {}

		virtual void handleShuttleCompleted(ShuttleInstance& _shuttle) = 0;
		virtual void cleanupCompletedShuttles(void) = 0;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_SHUTTLE_COMPLETION_SERVICE_HPP_