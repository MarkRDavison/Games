#ifndef INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_ENTITY_DATA_QUERY_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_ENTITY_DATA_QUERY_SERVICE_HPP_

#include <Sovereign/DataStructures/MoveableEntity.hpp>

namespace sov {

	class IEntityDataQueryService {
	protected:
		virtual ~IEntityDataQueryService(void) = 0;

	public:
		virtual bool doesEntityExistWithId(EntityId _id) const = 0;
		virtual bool doesMoveableEntityExistAtCoordinates(float _x, float _y) const = 0;

		virtual const MoveableEntity& getEntityById(EntityId _id) const = 0;
		virtual const MoveableEntity& getMoveableEntityAtCoordinates(float _x, float _y) const = 0;
	};

	inline IEntityDataQueryService::~IEntityDataQueryService(void) = default;

}

#endif // INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_ENTITY_DATA_QUERY_SERVICE_HPP_