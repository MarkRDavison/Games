#ifndef INCLUDED_ENTITY_COMPONENT_SYSTEM_COMPONENT_HPP_
#define INCLUDED_ENTITY_COMPONENT_SYSTEM_COMPONENT_HPP_

#include <SFML/Graphics.hpp>

namespace ecs {
	class Entity;
	struct Component {
		virtual ~Component(void) {}

		virtual void init(void) {}
		virtual void update(float _delta) {}
		virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const { }

		Entity *entity;
	};
}

#endif // INCLUDED_ENTITY_COMPONENT_SYSTEM_COMPONENT_HPP_