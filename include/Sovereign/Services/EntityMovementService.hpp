#ifndef INCLUDED_SOVEREIGN_SERVICES_ENTITY_MOVEMENT_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_ENTITY_MOVEMENT_SERVICE_HPP_

#include <Sovereign/Services/Interfaces/ICollisionDetectionService.hpp>
#include <Sovereign/Services/Interfaces/ICollisionResponseService.hpp>
#include <Sovereign/Services/Interfaces/IEntityMovementService.hpp>
#include <Sovereign/DataStructures/EntityData.hpp>

namespace sov {

	class EntityMovementService : public IEntityMovementService {
	public:
		EntityMovementService(EntityData& _entityData, ICollisionDetectionService& _collisionDetectionService, ICollisionResponseService& _collisionResponseService);
		~EntityMovementService(void) override;

		void updateAllMoveableEntities(float _delta) override;
		void updateMoveableEntity(MoveableEntity& _moveableEntity, float _delta) const override;

		static sf::Vector2f resolveCollisions(MoveableEntity& _moveableEntity, ICollisionDetectionService& _collisionDetectionService);
	protected:
		EntityData& m_EntityData;
		ICollisionDetectionService& m_CollisionDetectionService;
		ICollisionResponseService& m_CollisionResponseService;
	};

}

#endif // INCLUDED_SOVEREIGN_SERVICES_ENTITY_MOVEMENT_SERVICE_HPP_