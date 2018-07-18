#ifndef INCLUDED_EXPEDITION_UTILITY_COLLISION_HPP_
#define INCLUDED_EXPEDITION_UTILITY_COLLISION_HPP_

#include <SFML/System/Vector2.hpp>

namespace inf {
	class Collision {
		Collision(void) = delete;
		~Collision(void) = delete;
	public:

		static bool lineSegmentCollision(const sf::Vector2f& _line1Start, const sf::Vector2f& _line1End, const sf::Vector2f& _line2Start, const sf::Vector2f& _line2End, sf::Vector2f& _collision, float _determinantThreshold = -1.0f);
	};
}

#endif // INCLUDED_EXPEDITION_UTILITY_COLLISION_HPP_