#include <Sovereign/Services/CollisionResponseService.hpp> 
#include <Sovereign/Core/Definitions.hpp>
#include <cmath>

namespace sov {

	CollisionResponseService::~CollisionResponseService(void) {
		
	}

	float CollisionResponseService::getResolvedMovementFromCollision(float _collisionIntersectionOverlap, float _originalMovement) {
		if (std::abs(_collisionIntersectionOverlap) > std::abs(_originalMovement) + Definitions::Epsilon) {
			return _originalMovement;
		}

		if (_originalMovement < 0.0f) {
			return _originalMovement + _collisionIntersectionOverlap;
		}
		return _originalMovement - _collisionIntersectionOverlap;
	}

}
