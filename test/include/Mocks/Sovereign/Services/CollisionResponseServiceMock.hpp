#ifndef INCLUDED_MOCKS_SOVEREIGN_SERVICES_COLLISION_RESPONSE_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_SOVEREIGN_SERVICES_COLLISION_RESPONSE_SERVICE_MOCK_HPP_

#include <Sovereign/Services/Interfaces/ICollisionResponseService.hpp>
#include <Utility/TestSignal.hpp>

namespace sov {

	class CollisionResponseServiceMock : public ICollisionResponseService {
	public:
		~CollisionResponseServiceMock(void) override {}

		float getResolvedMovementFromCollision(float _collisionIntersectionOverlap, float _originalMovement) override {
			return getResolvedMovementFromCollisionCallback(_collisionIntersectionOverlap, _originalMovement);
		}

		inf::TestSignal<float, float, float> getResolvedMovementFromCollisionCallback;
	};
}

#endif // INCLUDED_MOCKS_SOVEREIGN_SERVICES_COLLISION_RESPONSE_SERVICE_MOCK_HPP_