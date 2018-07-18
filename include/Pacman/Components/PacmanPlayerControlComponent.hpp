#ifndef INCLUDED_PACMAN_COMPONENTS_PACMAN_CONTROL_COMPONENT_HPP_
#define INCLUDED_PACMAN_COMPONENTS_PACMAN_CONTROL_COMPONENT_HPP_

#include <Pacman/Components/PacmanAnimationComponent.hpp>
#include <Pacman/Components/PositionComponent.hpp>

#include <Pacman/GameObjects/Board.hpp>

#include <EntityComponentSystem/Component.hpp>
#include <EntityComponentSystem/Entity.hpp>

#include <Utility/Orientation.hpp>

#include <iostream>
#include <cmath>

#define SPEED 8.0f

namespace pacman {
	struct PacmanControlComponent : ecs::Component {
		PacmanAnimationComponent *animation{ nullptr };
		PositionComponent *position{ nullptr };
		Board *board{ nullptr };
		inf::Orientation currentOrientation{ inf::Orientation::Up };
		inf::Orientation nextOrientation{ inf::Orientation::Up };
		bool movingVertically{ false };
		bool movingHorizontally{ false };
		bool stuck{ false };
		sf::Vector2i cellPosition{};
		std::function<void(const sf::Vector2i&)> cellEntered{ nullptr };

		PacmanControlComponent(Board *_board) :
			board(_board) {
			
		}
		
		void init(void) override {
			animation = &entity->getComponent<PacmanAnimationComponent>();
			position = &entity->getComponent<PositionComponent>();
		}

		bool canMoveInDirection(inf::Orientation _orientation) const {
			const sf::Vector2i desiredCellCoords = sf::Vector2i(
				static_cast<unsigned int>(position->position.x),
				static_cast<unsigned int>(position->position.y)
			) + inf::OrientationToDirectionInt(_orientation);
			if (desiredCellCoords.x >= board->width || desiredCellCoords.x < 0 || desiredCellCoords.y >= board->height || desiredCellCoords.y < 0) {
				std::cout << "Going over the edge, TODO" << std::endl;
				return false;
			}
			const BoardCell& cell = board->m_BoardCells[desiredCellCoords.y * board->width + desiredCellCoords.x];
			return cell.isOpen;
		}

		void movePosition(const sf::Vector2f& _offset) {
			position->position += _offset;

			const int x = std::round(position->position.x + 0.5f);
			const int y = std::round(position->position.y + 0.5f);

			if (sf::Vector2i(x, y) != cellPosition) {
				cellPosition = { x,y };
				if (cellEntered) {
					cellEntered(cellPosition);
				}
			}

		}

		void move(inf::Orientation _orientation, const float _offset) {
			bool stuck{ false };
			const float distanceTillNextHorizontalCenter = std::fmod(position->position.x, 1.0f);
			const float distanceTillNextVerticalCenter = std::fmod(position->position.y, 1.0f);

			if (inf::IsVertical(_orientation) && distanceTillNextVerticalCenter == 0.0f) {
				if (!canMoveInDirection(_orientation)) {
					stuck = true;
					if (inf::IsHorizontal(nextOrientation) || inf::IsDirectionOpposite(_orientation, nextOrientation)) {
						if (canMoveInDirection(nextOrientation)) {
							movingHorizontally = inf::IsHorizontal(nextOrientation);
							movingVertically = inf::IsVertical(nextOrientation);
							currentOrientation = nextOrientation;
							move(currentOrientation, _offset);
							return;
						}
					}
				}
			}

			if (inf::IsHorizontal(_orientation) && distanceTillNextHorizontalCenter == 0.0f) {
				if (!canMoveInDirection(_orientation)) {
					stuck = true;
					if (inf::IsVertical(nextOrientation) || inf::IsDirectionOpposite(_orientation, nextOrientation)) {
						if (canMoveInDirection(nextOrientation)) {
							movingHorizontally = inf::IsHorizontal(nextOrientation);
							movingVertically = inf::IsVertical(nextOrientation);
							currentOrientation = nextOrientation;
							move(currentOrientation, _offset);
							return;
						} else {
							stuck = true;
						}
					}
				}
			}

			if (inf::IsDirectionOpposite(_orientation, nextOrientation)) {
				if (canMoveInDirection(nextOrientation)) {
					movingHorizontally = inf::IsHorizontal(nextOrientation);
					movingVertically = inf::IsVertical(nextOrientation);
					currentOrientation = nextOrientation;
					move(currentOrientation, _offset);
					return;
				}
			}

			animation->moving = !stuck;
			if (stuck) {
				return;
			}

			if (_orientation == inf::Orientation::Left) {
				const float distanceToLeftCenter = position->position.x - std::floor(position->position.x);
				if (distanceToLeftCenter == 0.0f || distanceToLeftCenter > _offset) {
					movePosition(sf::Vector2f(-_offset, 0.0f));
					movingHorizontally = true;
					movingVertically = false;
					currentOrientation = _orientation;
				}
				else {
					movePosition(sf::Vector2f(-distanceToLeftCenter, 0.0f));
					if (nextOrientation == _orientation) {
						move(_orientation, _offset - distanceToLeftCenter);
						return;
					} else {
						if (canMoveInDirection(nextOrientation)) {
							move(nextOrientation, _offset - distanceToLeftCenter);
							return;
						}
					}
				}
			}
			if (_orientation == inf::Orientation::Right) {
				const float distanceToRightCenter = std::floor(position->position.x + 1.0f) - position->position.x;
				if (distanceToRightCenter == 0.0f || distanceToRightCenter > _offset) {
					movePosition(sf::Vector2f(+_offset, 0.0f));
					movingHorizontally = true;
					movingVertically = false;
					currentOrientation = _orientation;
				}
				else {
					movePosition(sf::Vector2f(+distanceToRightCenter, 0.0f));
					if (nextOrientation == _orientation) {
						move(_orientation, _offset - distanceToRightCenter);
						return;
					}
					else {
						if (canMoveInDirection(nextOrientation)) {
							move(nextOrientation, _offset - distanceToRightCenter);
							return;
						}
					}
				}
			}
			if (_orientation == inf::Orientation::Up) {
				const float distanceToUpCenter = position->position.y - std::floor(position->position.y);
				if (distanceToUpCenter == 0.0f || distanceToUpCenter > _offset) {
					movePosition(sf::Vector2f(0.0f, -_offset));
					movingVertically = true;
					movingHorizontally = false;
					currentOrientation = _orientation;
				}
				else {
					movePosition(sf::Vector2f(0.0f, -distanceToUpCenter));
					if (nextOrientation == _orientation) {
						move(_orientation, _offset - distanceToUpCenter);
						return;
					}
					else {
						if (canMoveInDirection(nextOrientation)) {
							move(nextOrientation, _offset - distanceToUpCenter);
							return;
						}
					}
				}
			}
			if (_orientation == inf::Orientation::Down) {
				const float distanceToDownCenter = std::floor(position->position.y + 1.0f) - position->position.y;
				if (distanceToDownCenter == 0.0f || distanceToDownCenter > _offset) {
					movePosition(sf::Vector2f(0.0f, +_offset));
					movingVertically = true;
					movingHorizontally = false;
					currentOrientation = _orientation;
				}
				else {
					movePosition(sf::Vector2f(0.0f, +distanceToDownCenter));
					if (nextOrientation == _orientation) {
						move(_orientation, _offset - distanceToDownCenter);
						return;
					}
					else {
						if (canMoveInDirection(nextOrientation)) {
							move(nextOrientation, _offset - distanceToDownCenter);
							return;
						}
					}
				}
			}

		}

		void update(float _delta) override {
			if (animation->currentAnimation == PacmanAnimationComponent::PacmanAnimation::Die) {
				return;
			}

			inf::Orientation newOrientation = inf::Orientation::None;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				newOrientation = inf::Orientation::Up;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				newOrientation = inf::Orientation::Left;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				newOrientation = inf::Orientation::Down;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				newOrientation = inf::Orientation::Right;
			}

			if (newOrientation != inf::Orientation::None) {
				nextOrientation = newOrientation;
			}

			const float offset = _delta * SPEED;
			move(currentOrientation, offset);

			switch (currentOrientation) {
			case inf::Orientation::Left:
				animation->currentAnimation = PacmanAnimationComponent::PacmanAnimation::MoveLeft;
				break;
			case inf::Orientation::Right:
				animation->currentAnimation = PacmanAnimationComponent::PacmanAnimation::MoveRight;
				break;
			case inf::Orientation::Down:
				animation->currentAnimation = PacmanAnimationComponent::PacmanAnimation::MoveDown;
				break;
			case inf::Orientation::Up:
				animation->currentAnimation = PacmanAnimationComponent::PacmanAnimation::MoveUp;
				break;
			default:
				break;
			}
		}

	};
}

#endif // INCLUDED_PACMAN_COMPONENTS_PACMAN_CONTROL_COMPONENT_HPP_