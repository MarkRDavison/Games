#include <Hurricane/Objects/Level.hpp>

namespace hur {
	
	Level::Level(ecs::EntityManager& _entityManager) :
		m_EntityManager(_entityManager) {
		
	}

	ecs::EntityManager& Level::getEntityManager(void) const {
		return m_EntityManager;
	}
}