#include <Intrusion/Infrastructure/EntityFactory.hpp>

namespace itr {

	EntityFactory::EntityFactory(ecs::EntityManager& _entityManager) :
		m_EntityManager(_entityManager) {
		
	}
	EntityFactory::~EntityFactory(void) {
		
	}

}