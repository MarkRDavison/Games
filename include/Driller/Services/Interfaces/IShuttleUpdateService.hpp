#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_SHUTTLE_UPDATE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_SHUTTLE_UPDATE_SERVICE_HPP_

namespace drl {
	
	class IShuttleUpdateService {
	public:
		virtual ~IShuttleUpdateService(void) = 0 {}

		virtual void update(float _delta) = 0;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_SHUTTLE_UPDATE_SERVICE_HPP_