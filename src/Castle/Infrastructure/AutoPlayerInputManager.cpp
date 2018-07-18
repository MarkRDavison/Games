#include <Castle/Infrastructure/AutoPlayerInputManager.hpp>

namespace castle {

	AutoPlayerInputManager::~AutoPlayerInputManager(void) {
		m_Keys[sf::Keyboard::A] = false;
		m_Keys[sf::Keyboard::S] = false;
		m_Keys[sf::Keyboard::W] = false;
		m_Keys[sf::Keyboard::D] = false;
		m_Keys[sf::Keyboard::Space] = false;
	}

	bool AutoPlayerInputManager::isKeyPressed(sf::Keyboard::Key _key) {
		return m_Keys[_key];
	}
	void AutoPlayerInputManager::update(ecs::Entity * _playerEntity)
	{
	}
}