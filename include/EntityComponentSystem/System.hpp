#ifndef INCLUDED_ENTITY_COMPONENT_SYSTEM_SYSTEM_HPP_
#define INCLUDED_ENTITY_COMPONENT_SYSTEM_SYSTEM_HPP_

#include <EntityComponentSystem/EntityManager.hpp>
#include <SFML/Window/Event.hpp>

namespace ecs {
	class System {
	public:
		System(void) = default;
		virtual ~System() = default;
		virtual void update(float _delta, ecs::EntityManager& _entityManager) {}
		virtual bool handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) { return false; }
	};
}

#endif // INCLUDED_ENTITY_COMPONENT_SYSTEM_SYSTEM_HPP_