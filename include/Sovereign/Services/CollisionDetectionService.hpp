#ifndef INCLUDED_SOVEREIGN_SERVICES_COLLISION_DETECTION_SERVICE_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_COLLISION_DETECTION_SERVICE_SERVICE_HPP_

#include <Sovereign/Services/Interfaces/ICollisionDetectionService.hpp>
#include <Sovereign/Services/Interfaces/ILevelDataMutationService.hpp>
#include <Sovereign/Services/Interfaces/ILevelDataQueryService.hpp>
#include <Sovereign/DataStructures/LevelData.hpp>

namespace sov {

	class CollisionDetectionService : public ICollisionDetectionService{
	public:
		CollisionDetectionService(const LevelData& _levelData, ILevelDataMutationService& _levelDataMutationService, ILevelDataQueryService& _levelDataQueryService);
		~CollisionDetectionService(void) override;

		EntityContainedCell getCellsContainingEntity(const MoveableEntity& _moveableEntity) override;
		bool detectTileCollisionOccured(const EntityContainedCell& _entityContainedCells) override;
		bool detectTileCollisionOccured(const EntityContainedCell& _entityContainedCells, sf::FloatRect& _intersectionBounds) override;

	private:
		const LevelData& m_LevelData;
		ILevelDataMutationService& m_LevelDataMutationService;
		ILevelDataQueryService& m_LevelDataQueryService;
	};

}

#endif // INCLUDED_SOVEREIGN_SERVICES_COLLISION_DETECTION_SERVICE_SERVICE_HPP_