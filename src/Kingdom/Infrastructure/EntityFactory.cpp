#include <Kingdom/Infrastructure/EntityFactory.hpp>

namespace kdm {

	EntityFactory::EntityFactory(ecs::EntityManager& _entityManager) :
		m_EntityManager(_entityManager) {
		
	}
	EntityFactory::~EntityFactory(void) {
		
	}

}