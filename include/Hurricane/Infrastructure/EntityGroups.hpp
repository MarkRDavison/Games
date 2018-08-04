#ifndef INCLUDED_HURRICANE_INFRASTRUCTURE_ENTITY_GROUPS_HPP_
#define INCLUDED_HURRICANE_INFRASTRUCTURE_ENTITY_GROUPS_HPP_

#include <cstdlib>

namespace hurr {

	enum EntityGroup : std::size_t {
		GPlayer,
		GKinematic,
		GCollideable,
		GProjectile,
		GEnemy
	};

}

#endif // INCLUDED_HURRICANE_INFRASTRUCTURE_ENTITY_GROUPS_HPP_


