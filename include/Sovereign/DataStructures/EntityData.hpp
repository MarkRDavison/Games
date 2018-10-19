#ifndef INCLUDED_SOVEREIGN_DATA_STRUCTURES_ENTITY_DATA_HPP_
#define INCLUDED_SOVEREIGN_DATA_STRUCTURES_ENTITY_DATA_HPP_

#include <Sovereign/DataStructures/MoveableEntity.hpp>
#include <vector>

namespace sov {
	
	struct EntityData {
		std::vector<MoveableEntity> moveableEntities;
		EntityId playerId;
	};

}

#endif // INCLUDED_SOVEREIGN_DATA_STRUCTURES_ENTITY_DATA_HPP_