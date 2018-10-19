#ifndef INCLUDED_SOVEREIGN_DATA_STRUCTURES_ENTITY_CONTAINED_CELL_HPP_
#define INCLUDED_SOVEREIGN_DATA_STRUCTURES_ENTITY_CONTAINED_CELL_HPP_
#include <SFML/Graphics/Rect.hpp>

namespace sov {
	
	struct EntityContainedCell {
		bool valid{ false };

		int top{ 0 };
		int left{ 0 };
		int width{ 0 };
		int height{ 0 };

		sf::FloatRect entityBounds;
	};

}

#endif // INCLUDED_SOVEREIGN_DATA_STRUCTURES_ENTITY_CONTAINED_CELL_HPP_