#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_PROVIDED_JOB_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_PROVIDED_JOB_HPP_

#include <Driller/DataStructures/JobPrototype.hpp>

#include <SFML/System/Vector2.hpp>

namespace drl {
	
	struct BuildingProvidedJob {
		sf::Vector2i location;
		JobPrototypeId prototypeId;
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_PROVIDED_JOB_HPP_