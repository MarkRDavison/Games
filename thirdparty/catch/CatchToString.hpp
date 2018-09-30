#ifndef INCLUDED_TEST_CATCH_TO_STRING_HPP_
#define INCLUDED_TEST_CATCH_TO_STRING_HPP_

#include <Utility/Orientation.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>


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
	struct StringMaker<sf::Vector2u> {
		static std::string convert(sf::Vector2u const& _value) {
			return "x: " + std::to_string(_value.x) + ", y: " + std::to_string(_value.y);
		}
	};

	template<>
	struct StringMaker<inf::Orientation> {
		static std::string convert(inf::Orientation const& _value) {
			switch (_value) {
			case inf::Orientation::Up:
				return "Up";
			case inf::Orientation::Right:
				return "Right";
			case inf::Orientation::Down:
				return "Down";
			case inf::Orientation::Left:
				return "v";
			case inf::Orientation::None:
				return "None";
			default:
				return "Not defined orientation";
			}
		}
	};
}

#endif // INCLUDED_TEST_CATCH_TO_STRING_HPP_