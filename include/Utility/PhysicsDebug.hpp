#ifndef INCLUDED_UTILITY_PHYSICS_DEBUG_HPP_
#define INCLUDED_UTILITY_PHYSICS_DEBUG_HPP_

#include <SFML/Graphics.hpp>
#include <tinyheaders/tinyc2.h>

namespace inf {
	class PhysicsDebug {
	private:
		sf::RenderTarget& m_Target;

	public:
		PhysicsDebug(sf::RenderTarget& _target);

		void draw(const c2Poly& _poly, sf::Color _color = sf::Color::White, sf::RenderStates _states = sf::RenderStates::Default) const;

		void draw(const c2Circle& _body, sf::Color _color = sf::Color::White, sf::RenderStates _states = sf::RenderStates::Default) const;

		void draw(const c2AABB& _aabb, sf::Color _color = sf::Color::White, sf::RenderStates _states = sf::RenderStates::Default) const;

		void draw(const c2Ray& _ray, sf::Color _color = sf::Color::White, sf::RenderStates _states = sf::RenderStates::Default) const;

		void draw(const c2Capsule& _capsule, sf::Color _color = sf::Color::White, sf::RenderStates _states = sf::RenderStates::Default) const;

		void draw(const c2v& _point1, const c2v& _point2, sf::Color _color = sf::Color::White, sf::RenderStates _states = sf::RenderStates::Default) const;

		void draw(const c2v& _point, sf::Color _color = sf::Color::White, sf::RenderStates _states = sf::RenderStates::Default) const;

		void draw(const c2Manifold& _manifold, sf::Color _color = sf::Color::White, sf::RenderStates _states = sf::RenderStates::Default) const;

		void draw(const c2Raycast& _cast, const c2Ray& _ray, sf::Color _color = sf::Color::White, sf::RenderStates _states = sf::RenderStates::Default) const;
	};
}

#endif // INCLUDED_UTILITY_PHYSICS_DEBUG_HPP_