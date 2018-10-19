#ifndef INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_ENTITY_MOVEMENT_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_ENTITY_MOVEMENT_SERVICE_HPP_
#include <Sovereign/DataStructures/MoveableEntity.hpp>

namespace sov {
	
	class IEntityMovementService {
	protected:
		virtual ~IEntityMovementService(void) = 0 {}

	public:
		virtual void updateAllMoveableEntities(float _delta) = 0;
		virtual void updateMoveableEntity(MoveableEntity& _moveableEntity, float _delta) const = 0;
	};

}

#endif // INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_ENTITY_MOVEMENT_SERVICE_HPP_