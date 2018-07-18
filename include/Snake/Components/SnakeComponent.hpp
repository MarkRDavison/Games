#ifndef INCLUDED_SNAKE_COMPONENTS_SNAKE_COMPONENT_HPP_
#define INCLUDED_SNAKE_COMPONENTS_SNAKE_COMPONENT_HPP_

#include <Snake/Components/PositionComponent.hpp>

#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/Component.hpp>

namespace snake {
	
	struct SnakeComponent : ecs::Component {
		SnakeComponent *parent{nullptr};
		PositionComponent *position{ nullptr };
		inf::Orientation orientation{ inf::Orientation::None };
		inf::Orientation previousOrientation{ inf::Orientation::None };

		int index{ 0 };
		bool dead{ false };
		bool moved{ false };
		float timeToMove{ 0.0f };
		float timeToMoveCap{ 0.0f };
		sf::Vector2f previousPosition;
		std::function<bool(SnakeComponent *, const sf::Vector2f&)> onParentEnteringCell;

		SnakeComponent(SnakeComponent *_parent, float _timeToMove, inf::Orientation _orientation) : 
			parent(_parent), 
			timeToMove(_timeToMove), 
			timeToMoveCap(_timeToMove),
			orientation(_orientation),
			previousOrientation(_orientation) {
			
		}

		void init() override {
			position = &entity->getComponent<PositionComponent>();
			previousPosition = position->position;
			if (parent != nullptr) {
				index = parent->index + 1;
			}
		}

		void update(float _delta) override {
			if (parent == nullptr) {
				updateParent(_delta);
			} else {
				updateBody(_delta);
			}
		}


		void updateParent(float _delta) {
			if (dead) {
				return;
			}
			timeToMove -= _delta;
			if (timeToMove <= 0.0f) {
				timeToMove += timeToMoveCap;
				if (!onParentEnteringCell || onParentEnteringCell(this, position->position + inf::OrientationToDirection(orientation))) {
					previousPosition = position->position;
					position->position += inf::OrientationToDirection(orientation);
					moved = true;
					previousOrientation = orientation;
				} else {
					dead = true;
				}
			} else {
				moved = false;

				inf::Orientation newOrientation = inf::Orientation::None;

				// TODO: Use input manager???
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

				if (newOrientation != inf::Orientation::None && !inf::IsDirectionOpposite(orientation, newOrientation)) {
					orientation = newOrientation;
				}
			}
		}

		void updateBody(float _delta) {
			if (parent->moved) {
				const auto destination = parent->previousPosition;
				if (destination != parent->position->position) {
					previousPosition = position->position;
					position->position = destination;
				}

				previousOrientation = orientation;
				orientation = parent->previousOrientation;
				moved = true;
			} else {
				moved = false;
			}
		}
	};

}

#endif // INCLUDED_SNAKE_COMPONENTS_SNAKE_COMPONENT_HPP_