#ifndef INCLUDED_MOCKS_SOVEREIGN_SERVICES_COLLISION_DETECTION_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_SOVEREIGN_SERVICES_COLLISION_DETECTION_SERVICE_MOCK_HPP_

#include <Sovereign/Services/Interfaces/ICollisionDetectionService.hpp>
#include <Utility/TestSignal.hpp>

namespace sov {
	
	class CollisionDetectionServiceMock : public ICollisionDetectionService {
	public:
		~CollisionDetectionServiceMock(void) override {}

		EntityContainedCell getCellsContainingEntity(const MoveableEntity& _moveableEntity) override {
			return getCellsContainingEntityCallback.invoke(_moveableEntity);
		}

		bool detectTileCollisionOccured(const EntityContainedCell& _entityContainedCells) override {
			sf::FloatRect bounds{};
			return detectTileCollisionOccured(_entityContainedCells, bounds);
		}
		bool detectTileCollisionOccured(const EntityContainedCell& _entityContainedCells, sf::FloatRect& _intersectionBounds) override {
			return detectTileCollisionOccuredCallback.invoke(_entityContainedCells, _intersectionBounds);
		}

		inf::TestSignal<EntityContainedCell, const MoveableEntity&> getCellsContainingEntityCallback;
		inf::TestSignal<bool, const EntityContainedCell&, sf::FloatRect&> detectTileCollisionOccuredCallback;
	};

}

#endif // INCLUDED_MOCKS_SOVEREIGN_SERVICES_COLLISION_DETECTION_SERVICE_MOCK_HPP_