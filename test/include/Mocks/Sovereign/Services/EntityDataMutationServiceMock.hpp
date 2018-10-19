#ifndef INCLUDED_MOCKS_SOVEREIGN_SERVICES_ENTITY_DATA_MUTATION_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_SOVEREIGN_SERVICES_ENTITY_DATA_MUTATION_SERVICE_MOCK_HPP_

#include <Sovereign/Services/Interfaces/IEntityDataMutationService.hpp>
#include <Utility/TestSignal.hpp>

namespace sov {

	class EntityDataMutationServiceMock : public IEntityDataMutationService {
	public:
		~EntityDataMutationServiceMock(void) override {}

		void refreshEntities(void) override {
			refreshEntitiesCallback.invoke();
		}

		void removeEntity(EntityId _id) override {
			removeEntityCallback(_id);
		}
		void removeEntity(MoveableEntity _entity) override {
			removeEntityCallback(_entity.id);
		}

		bool mineEntity(EntityId _id, float _delta) override {
			return mineEntityCallback(_id, _delta);
		}
		bool mineEntity(MoveableEntity _entity, float _delta) override {
			return mineEntityCallback(_entity.id, _delta);
		}

		inf::TestSignal<void, void> refreshEntitiesCallback;
		inf::TestSignal<void, EntityId> removeEntityCallback;
		inf::TestSignal<bool, EntityId, float> mineEntityCallback;
	};

}

#endif // INCLUDED_MOCKS_SOVEREIGN_SERVICES_ENTITY_DATA_MUTATION_SERVICE_MOCK_HPP_