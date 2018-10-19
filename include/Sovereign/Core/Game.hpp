#ifndef INCLUDED_SOVEREIGN_CORE_GAME_HPP_
#define INCLUDED_SOVEREIGN_CORE_GAME_HPP_

#include <Sovereign/DataStructures/LevelData.hpp>
#include <Sovereign/DataStructures/EntityData.hpp>
#include <Sovereign/Services/Interfaces/ILevelDataQueryService.hpp>
#include <Sovereign/Services/Interfaces/ILevelDataMutationService.hpp>
#include <Sovereign/Services/Interfaces/ICollisionDetectionService.hpp>
#include <Sovereign/Services/Interfaces/ICollisionResponseService.hpp>
#include <Sovereign/Services/Interfaces/IEntityDataMutationService.hpp>
#include <Sovereign/Services/Interfaces/IEntityDataQueryService.hpp>
#include <Sovereign/Services/Interfaces/IEntityMovementService.hpp>
#include <Sovereign/Services/Interfaces/ILogService.hpp>
#include <Sovereign/Services/Interfaces/IPlayerControlService.hpp>
#include <Sovereign/DataStructures/ControlBindings.hpp>

namespace sov {

	class Game {
	public:
		Game(LevelData& _levelData, EntityData& _entityData, ControlBindings& _controlBindings, ILogService& _logService,
			ILevelDataQueryService& _levelDataQueryService, ILevelDataMutationService& _levelDataMutationService, 
			ICollisionDetectionService& _collisionDetectionService, ICollisionResponseService& _collisionResponseService, 
			IEntityDataQueryService& _entityDataQueryService, IEntityDataMutationService& _entityDataMutationService, IEntityMovementService& _entityMovementService,
			IPlayerControlService& _playerControlService);
		~Game(void);

		void update(float _delta) const;
		bool handleEvent(const sf::Event & _event) const;

		LevelData& m_LevelData;
		EntityData& m_EntityData;
		ControlBindings& m_ControlBindings;

		ILogService& m_LogService;
		ILevelDataQueryService& m_LevelDataQueryService;
		ILevelDataMutationService& m_LevelDataMutationService;
		ICollisionDetectionService& m_CollisionDetectionService;
		ICollisionResponseService& m_CollisionResponseService;
		IEntityDataQueryService& m_EntityDataQueryService;
		IEntityDataMutationService& m_EntityDataMutationService;
		IEntityMovementService& m_EntityMovementService;
		IPlayerControlService& m_PlayerControlService;
	};

}

#endif // INCLUDED_SOVEREIGN_CORE_GAME_HPP_