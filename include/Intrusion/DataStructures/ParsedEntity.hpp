#ifndef INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_ENTITY_HPP_
#define INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_ENTITY_HPP_

#include <string>
#include <Intrusion/Infrastructure/IntrusionDefinitions.hpp>
#include "ResourceBundle.hpp"

namespace itr {
	
	struct ParsedEntity {

		std::string prototypeName{ Definitions::DefaultEntityPrototypeName };
		std::string animationName{ Definitions::DefaultAnimationName };
		float health{ Definitions::DefaultEntityHealth};
		float speed{ Definitions::DefaultEntitySpeed };
		float intervalRange{ Definitions::DefaultIntervalRange };
		ResourceBundle drops;
	};

}

#endif // INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_ENTITY_HPP_