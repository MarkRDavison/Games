#ifndef INCLUDED_SOVEREIGN_SERVICES_ENTITY_DATA_QUERY_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_ENTITY_DATA_QUERY_SERVICE_HPP_

#include <Sovereign/Services/Interfaces/IEntityDataQueryService.hpp>
#include <Sovereign/DataStructures/EntityData.hpp>

namespace sov {

	class EntityDataQueryService : public IEntityDataQueryService {
	public:
		EntityDataQueryService(const EntityData& _entityData);
		~EntityDataQueryService(void) override;

		bool doesEntityExistWithId(EntityId _id) const override;
		bool doesMoveableEntityExistAtCoordinates(float _x, float _y) const override;

		const MoveableEntity& getEntityById(EntityId _id) const override;
		const MoveableEntity& getMoveableEntityAtCoordinates(float _x, float _y) const override;

	private:
		const EntityData& m_EntityData;
	};

}

#endif // INCLUDED_SOVEREIGN_SERVICES_ENTITY_DATA_QUERY_SERVICE_HPP_