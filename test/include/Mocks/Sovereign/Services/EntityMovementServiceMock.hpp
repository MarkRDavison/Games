#ifndef INCLUDED_MOCKS_SOVEREIGN_SERVICES_ENTITY_MOVEMENT_SERVICE_HPP_
#define INCLUDED_MOCKS_SOVEREIGN_SERVICES_ENTITY_MOVEMENT_SERVICE_HPP_

#include <Sovereign/Services/Interfaces/IEntityMovementService.hpp>
#include <Utility/TestSignal.hpp>

namespace sov {

	class EntityMovementServiceMock : public IEntityMovementService {
	public:
		~EntityMovementServiceMock(void) override {}

		void updateAllMoveableEntities(float _delta) override {
			updateAllMoveableEntitiesCallback(_delta);
		}
		void updateMoveableEntity(MoveableEntity& _moveableEntity, float _delta) const  override {
			updateMoveableEntityCallback.invoke(_moveableEntity, _delta);
		}

		inf::TestSignal<void, float> updateAllMoveableEntitiesCallback;
		inf::TestSignal<void, MoveableEntity&, float> updateMoveableEntityCallback;
	};

}

#endif // INCLUDED_SOVEREIGN_SINCLUDED_MOCKS_SOVEREIGN_SERVICES_ENTITY_MOVEMENT_SERVICE_HPP_ERVICES_ENTITY_MOVEMENT_SERVICE_HPP_