#ifndef INCLUDED_HURRICANE_OBJECTS_LEVEL_HPP_
#define INCLUDED_HURRICANE_OBJECTS_LEVEL_HPP_

#include <EntityComponentSystem/EntityManager.hpp>

#include <SFML/Graphics.hpp>

namespace hur {
	class Level {
	public:
		Level(ecs::EntityManager& _entityManager);

		ecs::EntityManager& getEntityManager(void) const;

	private:
		ecs::EntityManager& m_EntityManager;
	};
}

#endif // INCLUDED_HURRICANE_OBJECTS_LEVEL_HPP_