#ifndef INCLUDED_CASTLE_INFRASTRUCTURE_AUTO_PLAYER_INPUT_MANAGER_HPP_
#define INCLUDED_CASTLE_INFRASTRUCTURE_AUTO_PLAYER_INPUT_MANAGER_HPP_

#include <EntityComponentSystem/Entity.hpp>
#include <Infrastructure/InputManager.hpp>
#include <map>

namespace castle {
	class AutoPlayerInputManager : public inf::InputManager {
	public:
		~AutoPlayerInputManager(void) override;

		bool isKeyPressed(sf::Keyboard::Key _key) override;

		void update(ecs::Entity *_playerEntity);

		std::map<sf::Keyboard::Key, bool> m_Keys;
	};
}

#endif // INCLUDED_CASTLE_INFRASTRUCTURE_AUTO_PLAYER_INPUT_MANAGER_HPP_