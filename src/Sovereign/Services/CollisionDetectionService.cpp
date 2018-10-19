#include <Sovereign/Services/CollisionDetectionService.hpp>
#include <Sovereign/Core/Definitions.hpp>
#include <iostream>

namespace sov {

	CollisionDetectionService::CollisionDetectionService(const LevelData& _levelData, ILevelDataMutationService& _levelDataMutationService, ILevelDataQueryService& _levelDataQueryService) :
		m_LevelData(_levelData),
		m_LevelDataMutationService(_levelDataMutationService),
		m_LevelDataQueryService(_levelDataQueryService) {
		
	}
	CollisionDetectionService::~CollisionDetectionService(void) {
		
	}

	EntityContainedCell CollisionDetectionService::getCellsContainingEntity(const MoveableEntity& _moveableEntity) {
		EntityContainedCell cell{};

		cell.valid = true;

		const sf::Vector2f position = _moveableEntity.position + _moveableEntity.movement;

		const sf::Vector2f topLeftFloatPos = (position - _moveableEntity.size / 2.0f);
		const sf::Vector2f bottomRightFloatPos = (position + _moveableEntity.size / 2.0f);

		const sf::Vector2i topLeftCell{ static_cast<int>(std::floorf(topLeftFloatPos.x)) , static_cast<int>(std::floorf(topLeftFloatPos.y)) };
		const sf::Vector2i bottomRightCell{ static_cast<int>(std::floorf(bottomRightFloatPos.x)) , static_cast<int>(std::floorf(bottomRightFloatPos.y)) };

		cell.left = topLeftCell.x;
		cell.top = topLeftCell.y;

		cell.width = bottomRightCell.x - topLeftCell.x + 1;
		cell.height = bottomRightCell.y - topLeftCell.y + 1;

		cell.entityBounds = sf::FloatRect(position - _moveableEntity.size / 2.0f, _moveableEntity.size);

		return cell;
	}

	bool CollisionDetectionService::detectTileCollisionOccured(const EntityContainedCell& _entityContainedCells) {
		sf::FloatRect bounds{};
		return detectTileCollisionOccured(_entityContainedCells, bounds);
	}

	bool CollisionDetectionService::detectTileCollisionOccured(const EntityContainedCell& _entityContainedCells,	sf::FloatRect& _intersectionBounds) {
		for (int y = _entityContainedCells.top; y < _entityContainedCells.top + _entityContainedCells.height; ++y) {
			for (int x = _entityContainedCells.left; x < _entityContainedCells.left + _entityContainedCells.width; ++x) {
				const int chunkX = x / Definitions::ChunkSize;
				const int chunkY = y / Definitions::ChunkSize;

				if (!m_LevelDataQueryService.doesLevelChunkExist(chunkX, chunkY)) {
					return false;
				}

				const LevelChunkCell& cell = m_LevelDataQueryService.getLevelChunkCellForLevelChunk(chunkX, chunkY, x % Definitions::ChunkSize, y % Definitions::ChunkSize);

				if (!cell.empty) {
					// Set intersection bounds here. (TODO: Maybe change to manifold?)
					sf::FloatRect cellBounds({ static_cast<float>(x) * Definitions::TileSize, static_cast<float>(y) * Definitions::TileSize }, { Definitions::TileSize , Definitions::TileSize });
					if (cellBounds.intersects(_entityContainedCells.entityBounds, _intersectionBounds)) {
						return true;
					}
				}
			}
		}

		return false;
	}

}
