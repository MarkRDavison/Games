#ifndef INCLUDED_SOVEREIGN_SERVICES_ENTITY_DATA_MUTATION_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_ENTITY_DATA_MUTATION_SERVICE_HPP_

#include <Sovereign/Services/Interfaces/IEntityDataMutationService.hpp>
#include <Sovereign/DataStructures/EntityData.hpp>

namespace sov {
	
	class EntityDataMutationService : public IEntityDataMutationService {
	public:
		EntityDataMutationService(EntityData& _entityData);
		~EntityDataMutationService(void) override;

		void refreshEntities(void) override;
		void removeEntity(EntityId _id) override;
		void removeEntity(MoveableEntity _entity) override;

		bool mineEntity(EntityId _id, float _delta) override;
		bool mineEntity(MoveableEntity _entity, float _delta) override;

	protected:
		MoveableEntity& getEntityById(EntityId _id);
		const MoveableEntity& getEntityById(EntityId _id) const;

	private:
		EntityData& m_EntityData;
	};

}

#endif // INCLUDED_SOVEREIGN_SERVICES_ENTITY_DATA_MUTATION_SERVICE_HPP_