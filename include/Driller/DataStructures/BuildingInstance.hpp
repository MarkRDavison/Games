#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_INSTANCE_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_INSTANCE_HPP_

#include <Driller/Infrastructure/Definitions.hpp>
#include <SFML/System/Vector2.hpp>

namespace drl {

	struct BuildingInstance {
		EntityId Id;
		sf::Vector2u size;
		sf::Vector2u textureCoords; // Top left corner
		sf::Vector2i coordinates; // Top Left corner
		bool removalRequired{ false };
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_INSTANCE_HPP_