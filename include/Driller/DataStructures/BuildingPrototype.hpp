#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_PROTOTYPE_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_PROTOTYPE_HPP_

#include <cstdlib>
#include <SFML/System/Vector2.hpp>

namespace drl {

	using BuildingPrototypeId = std::size_t;

	struct BuildingPrototype {
		sf::Vector2u size;
		sf::Vector2u textureCoords;
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_PROTOTYPE_HPP_