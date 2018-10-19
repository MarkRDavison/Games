#ifndef INCLUDED_SOVEREIGN_DATA_STRUCTURES_CONTROL_BINDINGS_HPP_
#define INCLUDED_SOVEREIGN_DATA_STRUCTURES_CONTROL_BINDINGS_HPP_

#include <SFML/Window/Keyboard.hpp>

namespace sov {
	
	struct ControlBindings {
		sf::Keyboard::Key moveLeftBinding{ sf::Keyboard::A };
		sf::Keyboard::Key moveRightBinding{ sf::Keyboard::D };
		sf::Keyboard::Key moveUpBinding{ sf::Keyboard::W };
		sf::Keyboard::Key moveDownBinding{ sf::Keyboard::S };

		sf::Mouse::Button panButton{ sf::Mouse::Right };
		sf::Mouse::Button actionButtom{ sf::Mouse::Left };
	};

}

#endif // INCLUDED_SOVEREIGN_DATA_STRUCTURES_CONTROL_BINDINGS_HPP_