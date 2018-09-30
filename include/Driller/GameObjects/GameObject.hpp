#ifndef INCLUDED_DRILLER_GAME_OBJECTS_GAME_OBJECT_HPP_
#define INCLUDED_DRILLER_GAME_OBJECTS_GAME_OBJECT_HPP_

#include <SFML/Graphics.hpp>

namespace drl {
	
	class GameObject {
	public:
		virtual ~GameObject(void) = 0 {}

		virtual void update(float _delta) = 0;
		virtual bool handleEvent(const sf::Event & _event) { return false; };
		virtual void draw(sf::RenderTarget & _target, sf::RenderStates _states, float _alpha) const = 0;

		bool isAlive(void) const noexcept { return m_Alive; }
		void kill(void) noexcept { m_Alive = false; }

	protected:
		bool m_Alive{ true };
	};

}

#endif // INCLUDED_DRILLER_GAME_OBJECTS_GAME_OBJECT_HPP_