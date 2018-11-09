#ifndef INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_ENTITY_DATA_MUTATION_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_ENTITY_DATA_MUTATION_SERVICE_HPP_

#include <Sovereign/DataStructures/MoveableEntity.hpp>

namespace sov {
	
	class IEntityDataMutationService {
	protected:
		virtual ~IEntityDataMutationService(void) = 0;

	public:
		virtual void refreshEntities(void) = 0;

		virtual void removeEntity(EntityId _id) = 0;
		virtual void removeEntity(MoveableEntity _entity) = 0;

		virtual bool mineEntity(EntityId _id, float _delta) = 0;
		virtual bool mineEntity(MoveableEntity _entity, float _delta) = 0;
	};

	inline IEntityDataMutationService::~IEntityDataMutationService(void) = default;

}

#endif // INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_ENTITY_DATA_MUTATION_SERVICE_HPP_