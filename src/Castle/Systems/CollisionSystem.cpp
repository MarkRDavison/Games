#include <Castle/Systems/CollisionSystem.hpp>
#include <Castle/Components/PlayerComponent.hpp>
#include <Castle/Components/PositionComponent.hpp>
#include <Castle/Components/CollisionComponent.hpp>
#include <Castle/DataStructures/LevelCell.hpp>
#include <iostream>

#define EPSILON 0.00001f
#define MAGIC_RATIO_FOR_PASSENGER_DONT_KNOW_WHY 2.0f

namespace castle {

	CollisionSystem::CollisionSystem(void)  {
		
	}

	void CollisionSystem::update(float _delta, ecs::EntityManager& _entityManager, Level *_level) {
		collidingDynamicBodies.clear();
		for (ecs::Entity *e : _entityManager.getEntitiesByGroup(EntityGroup::GPlayer)) { // TODO: This should be controllable entity or something
			updateEntity(e, _delta, _level);
		}

		auto& collideableEntities = _entityManager.getEntitiesByGroup(EntityGroup::GCollideable);
		for (std::size_t i = 0u; i < collideableEntities.size(); ++i) {
			for (std::size_t j = i + 1; j < collideableEntities.size(); ++j) {
				handleCollisionComponentsCollide(collideableEntities[i], collideableEntities[j], _delta);
			}
		}
	}
	void CollisionSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		throw std::runtime_error("Must use the level specific update");
	}
	bool CollisionSystem::handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) {
		return false;
	}

	void CollisionSystem::updateEntity(ecs::Entity* _entity, float _delta, Level *_level) {
		auto& pos = _entity->getComponent<PositionComponent>();
		auto& col = _entity->getComponent<CollisionComponent>();
		auto& ply = _entity->getComponent<PlayerComponent>(); 

		// TODO: This can't take in a player component, extract to controlable entity component?
		// TODO: Crushing things seems very harsh, try moving them back if only slightly in the way? Crush Threshold? One way platforms only crush 1/4 ways
		// TODO: Jumping onto vertical moving block while going up and still moving (left/right keys) throws the player off sometimes
		// TODO: Create test scene to re-create hard to manually recreate
		// TODO: Frictionless surface/ice?
		// TODO: Springboard/jumpy thing

		col.isOnClimbable = col.isStillOnClimbable;
		col.isStillOnClimbable = false;
		col.collidedLeft = false;
		col.collidedRight = false;
		col.collidedBottom = false;
		col.collidedTop = false;

		doHorizontal(_delta, pos, col, ply, _level);
		doVertical(_delta, pos, col, ply, _level);

		col.movedLeft = false;
		col.movedRight = false;
		col.movedUp = false;
		col.movedDown = false;
	}

	void CollisionSystem::doHorizontal(float _delta, PositionComponent& pos, CollisionComponent& _collision, PlayerComponent& _player, Level *_level) {
		// Moving Right
		if (_collision.velocity.x > 0.0f || _collision.movedRight) {
			const unsigned currentX = pos.position.x + _collision.velocity.x * _delta + _collision.size.x / 2.0f;

			for (unsigned y = static_cast<unsigned>(pos.position.y - _collision.size.y); y <= static_cast<unsigned>(pos.position.y - EPSILON); ++y) {
				const LevelCell& c = _level->getCell(currentX, y);
				if (!c.empty) {
					const sf::FloatRect tileBounds(static_cast<float>(currentX), static_cast<float>(y), 1.0f, 1.0f);
					updateHorizontalVelocityBasedOnIntersection(_collision, pos, tileBounds, _delta);
					return;
				}
			}
		}
		// Moving left
		else if (_collision.velocity.x < 0.0f || _collision.movedLeft) {
			const unsigned currentX = pos.position.x + _collision.velocity.x * _delta - _collision.size.x / 2.0f;

			for (unsigned y = static_cast<unsigned>(pos.position.y - _collision.size.y); y <= static_cast<unsigned>(pos.position.y - EPSILON); ++y) {
				const LevelCell& c = _level->getCell(currentX, y);
				if (!c.empty) {
					const sf::FloatRect tileBounds(static_cast<float>(currentX), static_cast<float>(y), 1.0f, 1.0f);
					updateHorizontalVelocityBasedOnIntersection(_collision, pos, tileBounds, _delta);
					return;
				}
			}
		} 
	}

	void CollisionSystem::doVertical(float _delta, PositionComponent& pos, CollisionComponent& _collision, PlayerComponent& _player, Level *_level) {
		// Moving down
		if (_collision.velocity.y > 0.0f) {
			_player.onGround = false;
			const unsigned currentY = pos.position.y + _collision.velocity.y * _delta;
			for (unsigned x = static_cast<unsigned>(pos.position.x - _collision.size.x / 2.0f + EPSILON); x <= static_cast<unsigned>(pos.position.x + _collision.size.x / 2.0f - EPSILON); ++x) {
				const LevelCell& c = _level->getCell(x, currentY);
				if (!c.empty) {
					const sf::FloatRect tileBounds(static_cast<float>(x), static_cast<float>(currentY), 1.0f, 1.0f);
					updateVerticalVelocityBasedOnIntersection(_collision, pos, tileBounds, _delta);
					_player.onGround = true;
					_player.jumpLeft = PlayerComponent::JumpCount;
					_collision.isStillOnClimbable = false;
					return;
				}
			}
		}
		// Moving up
		else if (_collision.velocity.y < 0.0f) {
			const unsigned currentY = pos.position.y - _collision.size.y + _collision.velocity.y * _delta;
			for (unsigned x = static_cast<unsigned>(pos.position.x - _collision.size.x / 2.0f + EPSILON); x <= static_cast<unsigned>(pos.position.x + _collision.size.x / 2.0f - EPSILON); ++x) {
				const LevelCell& c = _level->getCell(x, currentY);
				if (!c.empty) {
					const sf::FloatRect tileBounds(static_cast<float>(x), static_cast<float>(currentY), 1.0f, 1.0f);
					updateVerticalVelocityBasedOnIntersection(_collision, pos, tileBounds, _delta);
					return;
				}
			}
		}
	}

	void CollisionSystem::handleCollisionComponentsCollide(ecs::Entity* _firstEntity, ecs::Entity* _secondEntity, float _delta) {
		CollisionComponent& first = _firstEntity->getComponent<CollisionComponent>();
		CollisionComponent& second = _secondEntity->getComponent<CollisionComponent>();

		if (!first.canCollide || !second.canCollide) {
			return;
		}
		
		if (first.impactsMovement && first.canBeMovedByOthers && second.impactsMovement && second.canBeMovedByOthers) {
			std::cout << "They both impact each other and can be impacted by each other, dunno what to do." << std::endl;
			return;
		}

		if (first.impactsMovement && !second.impactsMovement) {
			if (second.canBeMovedByOthers) {
				//std::cout << "first moves others, second doesnt and second can be moved, so the first one moves where it wants, the second one is moved" << std::endl;

				const sf::FloatRect firstBounds = sf::FloatRect(first.velocity * _delta + first.position->position - sf::Vector2f(first.size.x / 2.0f, first.size.y), first.size);
				const sf::FloatRect secondBounds = sf::FloatRect(second.velocity * _delta + second.position->position - sf::Vector2f(second.size.x / 2.0f, second.size.y), second.size);

				if (firstBounds.intersects(secondBounds)) {
					collidingDynamicBodies[_secondEntity].push_back(_firstEntity);
					return;
				}
			}
			else {
				//std::cout << "first moves others, second doesnt and second cannot be moved, so the first should just treat this like a transparent block" << std::endl;
				return;
			}
		}
		if (second.impactsMovement && !first.impactsMovement) {
			if (first.canBeMovedByOthers) {
				//std::cout << "second moves others, first doesnt and first can be moved, so the second one moves where it wants, the first one is moved" << std::endl;
				const sf::FloatRect firstBounds = sf::FloatRect(first.velocity * _delta + first.position->position - sf::Vector2f(first.size.x / 2.0f, first.size.y), first.size);
				const sf::FloatRect secondBounds = sf::FloatRect(second.velocity * _delta + second.position->position - sf::Vector2f(second.size.x / 2.0f, second.size.y), second.size);

				if (firstBounds.intersects(secondBounds)) {
					collidingDynamicBodies[_firstEntity].push_back(_secondEntity);
					return;
				}
			}
			else {
				//std::cout << "second moves others, first doesnt and second cannot be moved, so the second should just treat this like a transparent block" << std::endl;
				return;
			}
		}
		if (first.impactsMovement && second.impactsMovement && !first.canBeMovedByOthers && !second.canBeMovedByOthers) {
			// std::cout << "They both impact others, but both dont allow others to impact them, so just do nothing" << std::endl;
			return;
		}
		if (!first.impactsMovement || !second.impactsMovement) {
			// If either doesn't impact movement then this is just going through a hit box and not like the player hitting something solid or vice versa
			const sf::FloatRect firstBounds = sf::FloatRect(first.velocity * _delta + first.position->position - sf::Vector2f(first.size.x / 2.0f, first.size.y), first.size);
			const sf::FloatRect secondBounds = sf::FloatRect(second.velocity * _delta + second.position->position - sf::Vector2f(second.size.x / 2.0f, second.size.y), second.size);
			sf::FloatRect interactionBounds;

			if (firstBounds.intersects(secondBounds, interactionBounds)) {
				const float minX = std::min(firstBounds.width, secondBounds.width);
				const float minY = std::min(firstBounds.height, secondBounds.height);

				const float num = interactionBounds.width * interactionBounds.height;
				const float den = minX * minY;

				if (num / den > first.collisionThreshold) {
					if (first.callback) {
						first.callback(first, second);
					}
				}
				if (num / den > second.collisionThreshold) {
					if (second.callback) {
						second.callback(second, first);
					}
				}
			}
			return;
		}
		std::cout << "UNHANDLED" << std::endl;
	}

	void CollisionSystem::updateHorizontalVelocityBasedOnIntersection(CollisionComponent& _collisionComponent, PositionComponent& _positionComponent, const sf::FloatRect& _intersectionObjectBounds, float _delta) {
		if (_collisionComponent.velocity.x > 0.0f) {
			const float maxX = _intersectionObjectBounds.left - _collisionComponent.size.x / 2.0f;
			_collisionComponent.velocity.x = (maxX - _positionComponent.position.x) / _delta;
			_collisionComponent.collidedRight = true;
		}
		else if (_collisionComponent.movedRight) {
			const float maxX = _intersectionObjectBounds.left - _collisionComponent.size.x / 2.0f;
			_positionComponent.position.x = maxX;
			_collisionComponent.collidedRight = true;
		}
		else if (_collisionComponent.velocity.x < 0.0f) {
			const float minX = static_cast<float>(_intersectionObjectBounds.left + _intersectionObjectBounds.width) + _collisionComponent.size.x / 2.0f;
			_collisionComponent.velocity.x = (minX - _positionComponent.position.x) / _delta;
			_collisionComponent.collidedLeft = true;
		}
		else if (_collisionComponent.movedLeft) {
			const float minX = static_cast<float>(_intersectionObjectBounds.left + _intersectionObjectBounds.width) + _collisionComponent.size.x / 2.0f;
			_positionComponent.position.x = minX;
			_collisionComponent.collidedLeft = true;
		}
	}
	
	void CollisionSystem::updateVerticalVelocityBasedOnIntersection(CollisionComponent& _collisionComponent, PositionComponent& _positionComponent, const sf::FloatRect& _intersectionObjectBounds, float _delta) {
 		if (_collisionComponent.velocity.y > 0.0f) {
			const float maxY = static_cast<float>(_intersectionObjectBounds.top);
			if (_delta != 0.0f) {
				const float newVely = (maxY - _positionComponent.position.y) / _delta;
				_collisionComponent.velocity.y = newVely;
				_collisionComponent.collidedBottom = true;
			}
		} 
		else if (_collisionComponent.velocity.y < 0.0f) {
			const float minY = static_cast<float>(_intersectionObjectBounds.top + _intersectionObjectBounds.height) + _collisionComponent.size.y;
			if (_delta != 0.0f) {
				const float newVely = (minY - _positionComponent.position.y) / _delta;
				_collisionComponent.velocity.y = newVely;
				_collisionComponent.collidedTop = true;
			}
		}
	}

	bool CollisionSystem::detectCollisionAfterMovement(inf::Orientation _orientation, CollisionComponent& _collisionComponent, Level *_level) const {
		if (_orientation == inf::Orientation::Right) {
			const unsigned currentX = _collisionComponent.position->position.x + _collisionComponent.size.x / 2.0f - EPSILON;

			for (unsigned y = static_cast<unsigned>(_collisionComponent.position->position.y - _collisionComponent.size.y); y <= static_cast<unsigned>(_collisionComponent.position->position.y - EPSILON); ++y) {
				const LevelCell& c = _level->getCell(currentX, y);
				if (!c.empty) {
					return true;
				}
			}
		}
		if (_orientation == inf::Orientation::Left) {
			const unsigned currentX = _collisionComponent.position->position.x  - _collisionComponent.size.x / 2.0f + EPSILON;

			for (unsigned y = static_cast<unsigned>(_collisionComponent.position->position.y - _collisionComponent.size.y); y <= static_cast<unsigned>(_collisionComponent.position->position.y - EPSILON); ++y) {
				const LevelCell& c = _level->getCell(currentX, y);
				if (!c.empty) {
					return true;
				}
			}
		}
		if (_orientation == inf::Orientation::Up) {
			const unsigned currentY = _collisionComponent.position->position.y - _collisionComponent.size.y;
			for (unsigned x = static_cast<unsigned>(_collisionComponent.position->position.x - _collisionComponent.size.x / 2.0f + EPSILON); x <= static_cast<unsigned>(_collisionComponent.position->position.x + _collisionComponent.size.x / 2.0f - EPSILON); ++x) {
				const LevelCell& c = _level->getCell(x, currentY);
				if (!c.empty) {
					return true;
				}
			}
		}
		if (_orientation == inf::Orientation::Down) {
			const unsigned currentY = _collisionComponent.position->position.y;
			for (unsigned x = static_cast<unsigned>(_collisionComponent.position->position.x - _collisionComponent.size.x / 2.0f + EPSILON); x <= static_cast<unsigned>(_collisionComponent.position->position.x + _collisionComponent.size.x / 2.0f - EPSILON); ++x) {
				const LevelCell& c = _level->getCell(x, currentY);
				if (!c.empty) {
					return true;
				}
			}
		}

		return false;
	}

	static void setPlayerOnGround(ecs::Entity* entity) {
		if (entity->hasComponent<PlayerComponent>()) {
			entity->getComponent<PlayerComponent>().onGround = true;
			entity->getComponent<PlayerComponent>().jumpLeft = PlayerComponent::JumpCount;
		}
	}

	void CollisionSystem::handleMovementStuff(float _delta, Level *_level) {
		if (collidingDynamicBodies.size() > 0) {
			for (auto& colliders : collidingDynamicBodies) {
				ecs::Entity *entity = colliders.first;
				auto& cc = entity->getComponent<CollisionComponent>();
				for (auto collidee : colliders.second) {
					// entity just gets moved where the collidee's says
					auto& ccc = collidee->getComponent<CollisionComponent>();

					const sf::FloatRect firstBounds = sf::FloatRect(cc.position->position - sf::Vector2f(cc.size.x / 2.0f, cc.size.y), cc.size);
					const sf::FloatRect secondBounds = sf::FloatRect(ccc.position->position - sf::Vector2f(ccc.size.x / 2.0f, ccc.size.y), ccc.size);
					sf::FloatRect b;
					if (firstBounds.intersects(secondBounds, b)) {

						const float previousBottom = cc.position->previousPosition.y;
						const float currentBottom = cc.position->position.y;
						const float collideeTop = ccc.position->position.y - ccc.size.y;
						const float previousCollideeTop = ccc.position->previousPosition.y - ccc.size.y;
						const float previousCollideeBottom = ccc.position->previousPosition.y;
						const float previousTop = cc.position->previousPosition.y - cc.size.y;
						const float currentTop = cc.position->position.y - cc.size.y;
						const float collideeBottom = ccc.position->position.y;

						if (!ccc.isOneWay &&
							(previousCollideeBottom <= previousTop && currentTop <= collideeBottom || 
							previousTop >= collideeBottom && collideeBottom >= currentTop)) {
							cc.movedDown = true;
							cc.position->position.y = ccc.position->position.y + cc.size.y;
							cc.velocity.y = std::max(ccc.velocity.y, 0.0f);
							if (cc.collidedBottom) {
								std::cout << "Crushed from above!!!" << std::endl;
								entity->destroy();
								return;
							}
						}
						else if (
							(!cc.wantsToFallThrough || !ccc.isOneWay) && // TODO: Can no longer fall through top of ladder
							(collideeTop <= currentBottom && currentBottom <= previousCollideeTop || // something pushed up from the bottom
							(previousBottom == previousCollideeTop || previousBottom <= collideeTop) && collideeTop < currentBottom)){ // landed on top of something

							if (ccc.velocity.y < 0.0f) {
								cc.position->previousPosition = cc.position->position;
								cc.position->position.y = collideeTop;
								cc.movedUp = true;
								cc.velocity.y = 0;
								if (detectCollisionAfterMovement(inf::Orientation::Up, cc, _level)) {
									std::cout << "Crush from below" << std::endl;
									entity->destroy();
									return;
								}
							}
							else if (ccc.velocity.y > 0.0f) {
								cc.position->previousPosition = cc.position->position;
								cc.position->position.y = collideeTop;
								cc.movedDown = true;
								cc.velocity.y = ccc.velocity.y;
							}
							else {
								cc.position->previousPosition = cc.position->position;
								cc.position->position.y = collideeTop;
								cc.velocity.y = ccc.velocity.y;
							}
								
							if (ccc.velocity.x > 0.0f && !cc.collidedRight) {
								cc.position->previousPosition = cc.position->position;
								cc.movedRight = true;
								if (!cc.collidedLeft) {
									cc.position->position.x += (ccc.position->position.x - ccc.position->previousPosition.x) * MAGIC_RATIO_FOR_PASSENGER_DONT_KNOW_WHY;
									// TODO: WTF WHY? Doesn't work for diagonal platforms, and on left up right downs you fall off moving horizontal
								}
							}
							else if (ccc.velocity.x < 0.0f && !cc.collidedLeft) {
								cc.position->previousPosition = cc.position->position;
								cc.movedLeft = true;
								if (!cc.collidedRight) {
									cc.position->position.x += (ccc.position->position.x - ccc.position->previousPosition.x) * MAGIC_RATIO_FOR_PASSENGER_DONT_KNOW_WHY;
									// TODO: WTF WHY? Doesn't work for diagonal platforms, and on left up right downs you fall off moving horizontal
								}
							}

							setPlayerOnGround(entity);
						}
						else if (ccc.isClimeable) {
							if (cc.isOnClimbable) {
								cc.isStillOnClimbable = true;
							}
							if (cc.climbUp || cc.climbDown) {
								cc.isStillOnClimbable = true;
							}
							if (ccc.position->position.y - ccc.size.y> cc.position->position.y + cc.velocity.y * _delta) {
								cc.isStillOnClimbable = false;
								cc.isOnClimbable = false;
								cc.position->position.y = ccc.position->position.y - ccc.size.y;
								cc.velocity.y = 0.0f;
								setPlayerOnGround(entity);
							}
						}
						else {
							if (!ccc.isOneWay) { // Don't do horizontal collisions for one way top only platforms
								if (cc.position->position.x < ccc.position->position.x) {
									cc.position->position.x = ccc.position->position.x - (ccc.size.x + cc.size.x) / 2.0f;
									if (detectCollisionAfterMovement(inf::Orientation::Left, cc, _level)) {
										std::cout << "Crushed to the left!!!" << std::endl;
										entity->destroy();
										break;
									}
								}
								else
									if (cc.position->position.x > ccc.position->position.x) {
										cc.position->position.x = ccc.position->position.x + (ccc.size.x + cc.size.x) / 2.0f;
										if (detectCollisionAfterMovement(inf::Orientation::Right, cc, _level)) {
											std::cout << "Crushed to the Right!!!" << std::endl;
											entity->destroy();
											break;
										}
									}
							}
						}
					}
				}

				if (cc.movedLeft || cc.movedRight || cc.movedUp || cc.movedDown) {
					updateEntity(entity, 0.0f, _level);
				}
			}
		}
	}
}
