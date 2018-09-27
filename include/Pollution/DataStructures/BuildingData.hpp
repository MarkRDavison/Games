#ifndef POLLUTION_DATA_STRUCTURES_BUILDING_DATA_HPP_
#define POLLUTION_DATA_STRUCTURES_BUILDING_DATA_HPP_

#include <string>
#include <Infrastructure/DataStructures/ResourceBundle.hpp>
#include <SFML/Graphics/Color.hpp>

namespace pol {
	
	struct BuildingData {
		
		bool active{ false };
		int age;
		float dropRate;
		float accumulatedDropTime{ 0.0f };
		float accumulatedAnimationTime{ 0.0f };
		inf::ResourceBundle cost;
		inf::ResourceBundle drops;
		std::string animationName;
		sf::Color color{sf::Color::White};

	};

}

#endif // POLLUTION_DATA_STRUCTURES_BUILDING_DATA_HPP_