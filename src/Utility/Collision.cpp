#include <Utility/Collision.hpp>
#include <cstdlib>
#include <cmath>

namespace inf {

	int get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y, float _determinantThreshold) {
		const float s1_x = p1_x - p0_x;     
		const float s1_y = p1_y - p0_y;
		const float s2_x = p3_x - p2_x;     
		const float s2_y = p3_y - p2_y;

		const float det = -s2_x * s1_y + s1_x * s2_y;
		if (_determinantThreshold > 0.0f) {
			if (std::abs(det) < _determinantThreshold) {
				return 1;
			}
		}

		const float s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / det;
		const float t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / det;

		if (s > 0 && s < 1 && t > 0 && t < 1)
		{
			// Collision detected
			if (i_x != nullptr)
				*i_x = p0_x + (t * s1_x);
			if (i_y != nullptr)
				*i_y = p0_y + (t * s1_y);
			return 1;
		}

		return 0; // No collision
	}

	bool Collision::lineSegmentCollision(const sf::Vector2f& _line1Start, const sf::Vector2f& _line1End, const sf::Vector2f& _line2Start, const sf::Vector2f& _line2End, sf::Vector2f& _collision, float _determinantThreshold /*= 0*/) {

		return get_line_intersection(_line1Start.x, _line1Start.y, _line1End.x, _line1End.y, _line2Start.x, _line2Start.y, _line2End.x, _line2End.y, &_collision.x, &_collision.y, _determinantThreshold) == 1;
	}

}
