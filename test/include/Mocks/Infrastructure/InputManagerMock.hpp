#ifndef INCLUDED_MOCKS_INFRASTRUCTURE_INPUT_MANAGER_MOCK_HPP_
#define INCLUDED_MOCKS_INFRASTRUCTURE_INPUT_MANAGER_MOCK_HPP_

#include <functional>
#include <Infrastructure/InputManager.hpp>

namespace inf {
	
	class InputManagerMock : public InputManager {
	public:
		bool isKeyPressed(sf::Keyboard::Key _key) override {
			if (isKeyPressedCallback) {
				return isKeyPressedCallback(_key);
			}
			return false;
		}

		std::function<bool(sf::Keyboard::Key)> isKeyPressedCallback;
	};

}

#endif // INCLUDED_MOCKS_INFRASTRUCTURE_INPUT_MANAGER_MOCK_HPP_