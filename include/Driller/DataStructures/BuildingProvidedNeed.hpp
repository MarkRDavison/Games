#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_PROVIDED_NEED_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_PROVIDED_NEED_HPP_

#include <Driller/Infrastructure/Definitions.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdlib>

namespace drl {
	
	struct BuildingProvidedNeed {
		EntityId allocatedWorkerId{ 0u };
		sf::Vector2f offset;
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_PROVIDED_NEED_HPP_