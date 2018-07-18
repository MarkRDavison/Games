#ifndef INCLUDED_CASTLE_SYSTEMS_SYSTEM_HPP_
#define INCLUDED_CASTLE_SYSTEMS_SYSTEM_HPP_

#include <EntityComponentSystem/EntityManager.hpp>
#include <SFML/Window/Event.hpp>

namespace castle {
	class System {
	public:
		System(void) = default;
		virtual ~System() = default;
		virtual void update(float _delta, ecs::EntityManager& _entityManager) {}
		virtual bool handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) { return false; }
	};
}

#endif // INCLUDED_CASTLE_SYSTEMS_SYSTEM_HPP_