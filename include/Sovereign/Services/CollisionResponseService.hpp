#ifndef INCLUDED_SOVEREIGN_SERVICES_COLLISION_RESPONSE_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_COLLISION_RESPONSE_SERVICE_HPP_

#include <Sovereign/Services/Interfaces/ICollisionResponseService.hpp>

namespace sov {

	class CollisionResponseService : public ICollisionResponseService {
	public:
		~CollisionResponseService(void) override;

		float getResolvedMovementFromCollision(float _collisionIntersectionOverlap, float _originalMovement) override;
	};
	
}

#endif // INCLUDED_SOVEREIGN_SERVICES_COLLISION_RESPONSE_SERVICE_HPP_