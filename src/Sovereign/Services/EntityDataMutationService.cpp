#include <Sovereign/Services/EntityDataMutationService.hpp>
#include <algorithm>
#include <string>

namespace sov {

	EntityDataMutationService::EntityDataMutationService(EntityData& _entityData) :
		m_EntityData(_entityData) {

	}
	EntityDataMutationService::~EntityDataMutationService(void) {
		
	}

	void EntityDataMutationService::refreshEntities(void) {
		m_EntityData.moveableEntities.erase(std::remove_if(m_EntityData.moveableEntities.begin(), m_EntityData.moveableEntities.end(), [](const MoveableEntity& _me) -> bool {
			return _me.requiresRemoval;
		}), m_EntityData.moveableEntities.end());
	}
	void EntityDataMutationService::removeEntity(EntityId _id) {
		std::for_each(m_EntityData.moveableEntities.begin(), m_EntityData.moveableEntities.end(), [&_id](MoveableEntity& _me) -> void {
			if (_me.id == _id) {
				_me.requiresRemoval = true;
			}
		});
	}
	void EntityDataMutationService::removeEntity(MoveableEntity _entity) {
		removeEntity(_entity.id);
	}

	bool EntityDataMutationService::mineEntity(EntityId _id, float _delta) {
		MoveableEntity& me = getEntityById(_id);

		if (!me.isMineable) {
			throw std::runtime_error("MoveableEntity " + std::to_string(_id) + " is not mineable.");
		}

		me.mineTimeRemaining -= _delta;

		return me.mineTimeRemaining <= 0.0f;
	}
	bool EntityDataMutationService::mineEntity(MoveableEntity _entity, float _delta) {
		return mineEntity(_entity.id, _delta);
	}

	MoveableEntity& EntityDataMutationService::getEntityById(EntityId _id) {
		for (MoveableEntity& me : m_EntityData.moveableEntities) {
			if (me.id == _id) {
				return me;
			}
		}
		throw std::runtime_error("MoveableEntity " + std::to_string(_id) + " not found");
	}
	const MoveableEntity& EntityDataMutationService::getEntityById(EntityId _id) const {
		for (const MoveableEntity& me : m_EntityData.moveableEntities) {
			if (me.id == _id) {
				return me;
			}
		}
		throw std::runtime_error("MoveableEntity " + std::to_string(_id) + " not found");
	}
}
