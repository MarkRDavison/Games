#ifndef INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_COLLISION_DETECTION_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_COLLISION_DETECTION_SERVICE_HPP_

#include <Sovereign/DataStructures/EntityContainedCell.hpp>
#include <Sovereign/DataStructures/MoveableEntity.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace sov {
	
	class ICollisionDetectionService {
	protected:
		virtual ~ICollisionDetectionService(void) = 0;

	public:
		virtual EntityContainedCell getCellsContainingEntity(const MoveableEntity& _moveableEntity) = 0;
		virtual bool detectTileCollisionOccured(const EntityContainedCell& _entityContainedCells) = 0;
		virtual bool detectTileCollisionOccured(const EntityContainedCell& _entityContainedCells, sf::FloatRect& _intersectionBounds) = 0;
	};

	inline ICollisionDetectionService::~ICollisionDetectionService(void) = default;

}

#endif // INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_COLLISION_DETECTION_SERVICE_HPP_