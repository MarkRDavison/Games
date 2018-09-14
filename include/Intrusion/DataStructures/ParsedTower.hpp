#ifndef INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_TOWER_HPP_
#define INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_TOWER_HPP_

#include <string>

#include <SFML/System/Vector2.hpp>

#include <Intrusion/DataStructures/ResourceBundle.hpp>
#include <Intrusion/Infrastructure/IntrusionDefinitions.hpp>

namespace itr {
	
	struct ParsedTower {
		std::string prototypeName{ Definitions::DefaultTowerPrototypeName };
		std::string animationName{ Definitions::DefaultAnimationName };
		float range{ Definitions::DefaultTowerRange };
		sf::Vector2u size{ 1,1 };
		ResourceBundle cost;
	};

}

#endif // INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_TOWER_HPP_