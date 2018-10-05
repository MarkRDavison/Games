#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_SHUTTLE_CREATION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_SHUTTLE_CREATION_SERVICE_HPP_

#include <Driller/DataStructures/GameCommand.hpp>

namespace drl {
	
	class IShuttleCreationService {
	public:
		virtual ~IShuttleCreationService(void) = 0 {}

		virtual bool canCreateShuttle(const GameCommand::CreateShuttleEvent& _event) = 0;
		virtual void createShuttle(const GameCommand::CreateShuttleEvent& _event) = 0;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_SHUTTLE_CREATION_SERVICE_HPP_