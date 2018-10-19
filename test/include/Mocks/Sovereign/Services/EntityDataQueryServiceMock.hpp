#ifndef INCLUDED_MOCKS_SOVEREIGN_SERVICES_ENTITY_DATA_QUERY_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_SOVEREIGN_SERVICES_ENTITY_DATA_QUERY_SERVICE_MOCK_HPP_

#include <Sovereign/Services/Interfaces/IEntityDataQueryService.hpp>
#include <Utility/TestSignal.hpp>

namespace sov {

	class EntityDataQueryServiceMock : public IEntityDataQueryService {
	public:
		~EntityDataQueryServiceMock(void) override {}

		bool doesEntityExistWithId(EntityId _id) const override {
			return doesEntityExistWithIdCallback(_id);
		}
		bool doesMoveableEntityExistAtCoordinates(float _x, float _y) const override {
			return doesMoveableEntityExistAtCoordinatesCallback(_x, _y);
		}

		const MoveableEntity& getEntityById(EntityId _id) const override {
			return getEntityByIdCallback(_id);
		}
		const MoveableEntity& getMoveableEntityAtCoordinates(float _x, float _y) const override {
			return getMoveableEntityAtCoordinatesCallback(_x, _y);
		}

		inf::TestSignal<bool, EntityId> doesEntityExistWithIdCallback;
		inf::TestSignal<bool, float, float> doesMoveableEntityExistAtCoordinatesCallback;
		inf::TestSignal<const MoveableEntity&, EntityId> getEntityByIdCallback;
		inf::TestSignal<const MoveableEntity&, float, float> getMoveableEntityAtCoordinatesCallback;
	};

}

#endif // INCLUDED_MOCKS_SOVEREIGN_SERVICES_ENTITY_DATA_QUERY_SERVICE_MOCK_HPP_