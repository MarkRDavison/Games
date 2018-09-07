#ifndef INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_ENTITY_HPP_
#define INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_ENTITY_HPP_

#include <string>
#include <Intrusion/Infrastructure/IntrusionDefinitions.hpp>

namespace itr {
	
	struct ParsedEntity {

		std::string prototypeName{ Definitions::DefaultEntityPrototypeName };
		std::string animationName{ Definitions::DefaultAnimationName };
		int health{ Definitions::DefaultEntityHealth};
		float speed{ Definitions::DefaultEntitySpeed };

	};

}

#endif // INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_ENTITY_HPP_