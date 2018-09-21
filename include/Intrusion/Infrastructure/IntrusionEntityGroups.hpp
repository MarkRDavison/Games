#ifndef INCLUDED_INTRUSION_INFRASTRUCTURE_ENTITY_GROUPS_HPP_
#define INCLUDED_INTRUSION_INFRASTRUCTURE_ENTITY_GROUPS_HPP_

#include <cstdlib>

namespace itr {

	enum EntityGroup : std::size_t {
		GRenderable,
		GPathFollower,
		GTower,
		GTowerTarget,
		GProjectile,
		GLife
	};

}

#endif // INCLUDED_INTRUSION_INFRASTRUCTURE_ENTITY_GROUPS_HPP_


