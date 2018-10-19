#include <Sovereign/Core/Game.hpp>

namespace sov {

	Game::Game(LevelData& _levelData, EntityData& _entityData, ControlBindings& _controlBindings, ILogService& _logService,
		ILevelDataQueryService& _levelDataQueryService, ILevelDataMutationService& _levelDataMutationService, 
		ICollisionDetectionService& _collisionDetectionService, ICollisionResponseService& _collisionResponseService, 
		IEntityDataQueryService& _entityDataQueryService, IEntityDataMutationService& _entityDataMutationService, IEntityMovementService& _entityMovementService,
		IPlayerControlService& _playerControlService):
		m_LevelData(_levelData),
		m_EntityData(_entityData),
		m_ControlBindings(_controlBindings),
		m_LogService(_logService),
		m_LevelDataQueryService(_levelDataQueryService),
		m_LevelDataMutationService(_levelDataMutationService),
		m_CollisionDetectionService(_collisionDetectionService),
		m_CollisionResponseService(_collisionResponseService),
		m_EntityDataQueryService(_entityDataQueryService),
		m_EntityDataMutationService(_entityDataMutationService),
		m_EntityMovementService(_entityMovementService),
		m_PlayerControlService(_playerControlService) {

	}
	Game::~Game(void) {

	}

	void Game::update(float _delta) const {
		m_EntityMovementService.updateAllMoveableEntities(_delta);
		m_EntityDataMutationService.refreshEntities();

	}

	bool Game::handleEvent(const sf::Event& _event) const {
		if (m_PlayerControlService.handleEvent(_event)) {
			return true;
		}
		return false;
	}

}
