#ifndef INCLUDED_KINGDOM_INFRASTRUCTURE_ENTITY_FACTORY_HPP_
#define INCLUDED_KINGDOM_INFRASTRUCTURE_ENTITY_FACTORY_HPP_

#include <EntityComponentSystem/EntityManager.hpp>

namespace kdm {

	class EntityFactory {
	public:
		EntityFactory(ecs::EntityManager& _entityManager);
		~EntityFactory(void);

	private:
		ecs::EntityManager& m_EntityManager;
	};
	
}

#endif // INCLUDED_KINGDOM_INFRASTRUCTURE_ENTITY_FACTORY_HPP_