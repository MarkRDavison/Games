#include <Sovereign/Services/EntityMovementService.hpp>
#include <Utility/VectorMath.hpp>

namespace sov {

	EntityMovementService::EntityMovementService(EntityData& _entityData, ICollisionDetectionService& _collisionDetectionService, ICollisionResponseService& _collisionResponseService) :
		m_EntityData(_entityData),
		m_CollisionDetectionService(_collisionDetectionService),
		m_CollisionResponseService(_collisionResponseService) {
		
	}
	EntityMovementService::~EntityMovementService(void) {
		
	}

	void EntityMovementService::updateAllMoveableEntities(float _delta) {
		for (MoveableEntity& me : m_EntityData.moveableEntities) {
			updateMoveableEntity(me, _delta);
		}
	}

	void EntityMovementService::updateMoveableEntity(MoveableEntity& _moveableEntity, float _delta) const {
		sf::Vector2f playerDirection{};

		if (_moveableEntity.moveLeft) {
			playerDirection.x -= 1.0f;
		}
		if (_moveableEntity.moveRight) {
			playerDirection.x += 1.0f;
		}
		if (_moveableEntity.moveDown) {
			playerDirection.y += 1.0f;
		}
		if (_moveableEntity.moveUp) {
			playerDirection.y -= 1.0f;
		}

		if (playerDirection != sf::Vector2f()) {
			inf::VectorMath::normalise(playerDirection);

			sf::Vector2f move = playerDirection * _moveableEntity.speed * _delta;

			{
				_moveableEntity.movement.x = move.x;
				const sf::Vector2f offset = resolveCollisions(_moveableEntity, m_CollisionDetectionService);
				if (offset.x != 0.0f) {
					move.x = m_CollisionResponseService.getResolvedMovementFromCollision(offset.x, _moveableEntity.movement.x);
				}
				_moveableEntity.movement.x = 0.0f;  // to not mess with the y axis
			}

			{
				_moveableEntity.movement.y = move.y;
				const sf::Vector2f offset = resolveCollisions(_moveableEntity, m_CollisionDetectionService);
				if (offset.y != 0.0f) {
					_moveableEntity.movement.y = m_CollisionResponseService.getResolvedMovementFromCollision(offset.y, _moveableEntity.movement.y);
				}
				_moveableEntity.movement.x = move.x;
			}

			_moveableEntity.position += _moveableEntity.movement;
			_moveableEntity.movement = {};
		}
	}

	sf::Vector2f EntityMovementService::resolveCollisions(MoveableEntity& _moveableEntity, ICollisionDetectionService& _collisionDetectionService) {
		const EntityContainedCell& containingCells = _collisionDetectionService.getCellsContainingEntity(_moveableEntity);
		if (containingCells.valid) {
			sf::FloatRect intersectionBounds{};
			if (_collisionDetectionService.detectTileCollisionOccured(containingCells, intersectionBounds)) {
				return { intersectionBounds.width, intersectionBounds.height };
			}
		}
		return {};
	}

}
