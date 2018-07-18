#ifndef INCLUDED_UTILITY_ORIENTATION_HPP_
#define INCLUDED_UTILITY_ORIENTATION_HPP_

#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <string>

namespace inf {
	enum class Orientation {
		Up,
		Down,
		Left,
		Right,
		None
	};

	static sf::Vector2f OrientationToDirection(Orientation _orientation) {
		switch (_orientation) {
		case Orientation::Up:
			return { 0.0f, -1.0f };
		case Orientation::Down:
			return { 0.0f, +1.0f };
		case Orientation::Left:
			return { -1.0f, 0.0f };
		case Orientation::Right:
			return { +1.0f, 0.0f };
		default:
			return { 0.0f, 0.0f };
		}
	}
	static sf::Vector2i OrientationToDirectionInt(Orientation _orientation) {
		switch (_orientation) {
		case Orientation::Up:
			return { 0, -1 };
		case Orientation::Down:
			return { 0, +1 };
		case Orientation::Left:
			return { -1, 0 };
		case Orientation::Right:
			return { +1, 0 };
		default:
			return { 0, 0 };
		}
	}

	static bool IsDirectionOpposite(Orientation _first, Orientation _second) {
		return OrientationToDirectionInt(_first) == OrientationToDirectionInt(_second) * -1;
	}

	static bool IsHorizontal(Orientation _orientation) {
		return _orientation == Orientation::Left || _orientation == Orientation::Right;
	}
	static bool IsVertical(Orientation _orientation) {
		return _orientation == Orientation::Up || _orientation == Orientation::Down;
	}

	static std::string ToString(Orientation _orientation) {
		switch (_orientation) {
		case Orientation::Up:
			return "Up";
		case Orientation::Down:
			return "Down";
		case Orientation::Left:
			return "Left";
		case Orientation::Right:
			return "Right";
		default:
			return "None";
		}
	}

	static Orientation RandomOrientation(void) {
		switch (rand() % 4) {
		case 0:
			return Orientation::Up;
		case 1:
			return Orientation::Right;
		case 2:
			return Orientation::Left;
		default:
			return Orientation::Down;
		}
	}
}

#endif // INCLUDED_UTILITY_ORIENTATION_HPP_