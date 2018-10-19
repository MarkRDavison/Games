#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_PROTOTYPE_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_PROTOTYPE_HPP_

#include <Driller/DataStructures/WorkerPrototype.hpp>
#include <Driller/DataStructures/BuildingProvidedJob.hpp>

#include <Infrastructure/DataStructures/ResourceBundle.hpp>

#include <SFML/System/Vector2.hpp>

#include <cstdlib>


namespace drl {

	using BuildingPrototypeId = std::size_t;

	struct BuildingPrototype {
		sf::Vector2u size;
		sf::Vector2u textureCoords;

		WorkerPrototypeId providedWorkerPrototypeId{0u};
		int providedWorkerPrototypeAmount{-1};
		inf::ResourceBundle cost;
		bool providesJobs{ false };
		bool providesNeeds{ false };

		std::vector<BuildingProvidedJob> providedJobs;
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_BUILDING_PROTOTYPE_HPP_