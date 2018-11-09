#ifndef INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_COLLISION_RESPONSE_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_COLLISION_RESPONSE_SERVICE_HPP_

namespace sov {
	
	class ICollisionResponseService {
	protected:
		virtual ~ICollisionResponseService(void) = 0;

	public:
		virtual float getResolvedMovementFromCollision(float _collisionIntersectionOverlap, float _originalMovement) = 0;

	};

	inline ICollisionResponseService::~ICollisionResponseService(void) = default;

}

#endif // INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_COLLISION_RESPONSE_SERVICE_HPP_