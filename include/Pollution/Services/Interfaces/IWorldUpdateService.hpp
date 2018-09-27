#ifndef INCLUDED_POLLUTION_SERVICES_INTERFACES_I_WORLD_UPDATE_SERVICE_HPP_
#define INCLUDED_POLLUTION_SERVICES_INTERFACES_I_WORLD_UPDATE_SERVICE_HPP_

#include <Pollution/DataStructures/WorldData.hpp>

namespace pol {

	class IWorldUpdateService {
	public:
		virtual ~IWorldUpdateService(void) = 0 {}

		virtual void update(float _delta, WorldData& _worldData) = 0;
	};

}

#endif // #define INCLUDED_POLLUTION_SERVICES_INTERFACES_I_WORLD_UPDATE_SERVICE_HPP_
