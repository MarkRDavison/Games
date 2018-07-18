#ifndef INCLUDED_CASTLE_INFRASTRUCTURE_ENTITY_GROUPS_HPP_
#define INCLUDED_CASTLE_INFRASTRUCTURE_ENTITY_GROUPS_HPP_

#include <cstdlib>

namespace castle {

	enum EntityGroup : std::size_t {
		GPlayer,
		GInteractable,
		GCollideable,
		GWaypoint,
		GKinematic
	};

}

#endif // INCLUDED_CASTLE_INFRASTRUCTURE_ENTITY_GROUPS_HPP_


