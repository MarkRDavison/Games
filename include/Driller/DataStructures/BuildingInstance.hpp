#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_INSTANCE_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_INSTANCE_HPP_

#include <Driller/DataStructures/WorkerPrototype.hpp>
#include <Driller/DataStructures/BuildingProvidedNeed.hpp>
#include <Driller/Infrastructure/Definitions.hpp>
#include <SFML/System/Vector2.hpp>

namespace drl {

	struct BuildingInstance {
		EntityId Id;
		sf::Vector2u size;
		sf::Vector2u textureCoords; // Top left corner
		sf::Vector2i coordinates; // Top Left corner
		bool removalRequired{ false };
		
		WorkerPrototypeId providedWorkerPrototypeId;
		int providedWorkerPrototypeAmount;
		bool providesNeeds{ false };
		std::vector<BuildingProvidedNeed> providedNeeds;
		std::size_t providedNeedId{ 0u };
		float providedNeedRate{ 60.0f };
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_INSTANCE_HPP_