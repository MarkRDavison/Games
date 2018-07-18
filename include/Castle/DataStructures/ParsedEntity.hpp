#ifndef INCLUDED_CASTLE_DATA_STRUCTURE_PARSED_ENTITY_HPP_
#define INCLUDED_CASTLE_DATA_STRUCTURE_PARSED_ENTITY_HPP_

#include <string>
#include <SFML/System/Vector2.hpp>
#include <Sol2/sol.hpp>

namespace castle {
	struct ParsedEntity {
		std::string name;
		std::string prototype;
		sf::Vector2f size;
		sf::Vector2u coordinates;
		sol::table entityTable;
	};
}

#endif // INCLUDED_CASTLE_DATA_STRUCTURE_PARSED_ENTITY_HPP_