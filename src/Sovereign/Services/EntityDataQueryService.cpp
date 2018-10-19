#include <Sovereign/Services/EntityDataQueryService.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace sov {

	EntityDataQueryService::EntityDataQueryService(const EntityData& _entityData) :
		m_EntityData(_entityData) {
		
	}
	EntityDataQueryService::~EntityDataQueryService(void) {

	}

	bool EntityDataQueryService::doesEntityExistWithId(EntityId _id) const {
		for (const MoveableEntity& me : m_EntityData.moveableEntities) {
			if (me.id == _id) {
				return true;
			}
		}
		return false;
	}

	bool EntityDataQueryService::doesMoveableEntityExistAtCoordinates(float _x, float _y) const {
		for (const MoveableEntity& me : m_EntityData.moveableEntities) {
			if (sf::FloatRect(me.position - me.size / 2.0f, me.size).contains(_x, _y)) {
				return true;
			}
		}

		return false;
	}

	const MoveableEntity& EntityDataQueryService::getEntityById(EntityId _id) const {
		for (const MoveableEntity& me : m_EntityData.moveableEntities) {
			if (me.id == _id) {
				return me;
			}
		}
		throw std::runtime_error("MoveableEntity not within bounds");
	}

	const MoveableEntity& EntityDataQueryService::getMoveableEntityAtCoordinates(float _x, float _y) const {
		for (const MoveableEntity& me : m_EntityData.moveableEntities) {
			if (sf::FloatRect(me.position - me.size / 2.0f, me.size).contains(_x, _y)) {
				return me;
			}
		}
		throw std::runtime_error("MoveableEntity not within bounds");
	}

}
