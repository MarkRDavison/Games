#ifndef INCLUDED_TEST_CATCH_TO_STRING_HPP_
#define INCLUDED_TEST_CATCH_TO_STRING_HPP_

#include <SFML/System/Vector2.hpp>
#include <string>
#include <Expedition/Enumerations/Orientation.hpp>
#include <Expedition/Enumerations/MovementStateEnum.hpp>


namespace Catch {
	template<>
	struct StringMaker<sf::Vector2f> {
		static std::string convert(sf::Vector2f const& _value) {
			return "x: " + std::to_string(_value.x) + ", y: " + std::to_string(_value.y);
		}
	};
	template<>
	struct StringMaker<sf::Vector2i> {
		static std::string convert(sf::Vector2i const& _value) {
			return "x: " + std::to_string(_value.x) + ", y: " + std::to_string(_value.y);
		}
	};

	template<>
	struct StringMaker<expd::Orientation> {
		static std::string convert(expd::Orientation const& _value) {
			switch (_value) {
			case expd::Orientation::Up:
				return "Up";
			case expd::Orientation::Right:
				return "Right";
			case expd::Orientation::Down:
				return "Down";
			case expd::Orientation::Left:
				return "v";
			case expd::Orientation::None:
				return "None";
			default:
				return "Not defined orientation";
			}
		}
	};

	template<>
	struct StringMaker<expd::MovementStateEnum> {
		static std::string convert(expd::MovementStateEnum const& _value) {
			switch (_value) {
			case expd::MovementStateEnum::Idle:
				return "Idle";
			case expd::MovementStateEnum::InMotion:
				return "InMotion";
			default:
				return "Not defined orientation";
			}
		}
	};
}

#endif // INCLUDED_TEST_CATCH_TO_STRING_HPP_