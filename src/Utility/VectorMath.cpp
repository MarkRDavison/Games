#include <Utility/VectorMath.hpp>
#include <cmath>

namespace inf {
	namespace VectorMath {
		
		float length(const sf::Vector2f& _vec) {
			return static_cast<float>(sqrt(_vec.x * _vec.x + _vec.y * _vec.y));
		}

		
		float length(const sf::Vector3f& _vec) {
			return static_cast<float>(sqrt(_vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z));
		}

		
		float distance(const sf::Vector2f& _vec1, const sf::Vector2f& _vec2) {
			return length(_vec2 - _vec1);
		}

		
		float distance(const sf::Vector3f& _vec1, const sf::Vector3f& _vec2) {
			return length(_vec2 - _vec1);
		}


		
		float lengthSquared(const sf::Vector2f& _vec) {
			return _vec.x * _vec.x + _vec.y * _vec.y;
		}

		
		float lengthSquared(const sf::Vector3f& _vec) {
			return _vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z;
		}


		
		sf::Vector2f& normalise(sf::Vector2f& _vec) {
			_vec /= length(_vec);

			return _vec;
		}
		sf::Vector2f normalise(const sf::Vector2f& _vec) {
			return _vec / length(_vec);
		}

		
		sf::Vector3f& normalise(sf::Vector3f& _vec) {
			_vec /= length(_vec);

			return _vec;
		}


		
		sf::Vector3f cross(const sf::Vector3f& _left, const sf::Vector3f& _right) {
			return sf::Vector3f(
				_left.y * _right.z - _left.z * _right.y,
				_left.z * _right.x - _left.x * _right.z,
				_left.x * _right.y - _left.y * _right.x
			);
		}


		
		float dot(const sf::Vector2f& _left, const sf::Vector2f& _right) {
			return _left.x * _right.x + _left.y * _right.y;
		}

		
		float dot(const sf::Vector3f& _left, const sf::Vector3f& _right) {
			return _left.x * _right.x + _left.y * _right.y + _left.z * _right.z;
		}
		
		float toAngle(const sf::Vector2f& _vec) {
			return std::atan2(_vec.y, _vec.x);
		}

		sf::Vector2f toDirection(float _angle) {
			return sf::Vector2f(cosf(_angle), sinf(_angle));
		}
	}
}