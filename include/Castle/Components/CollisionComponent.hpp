#ifndef INCLUDED_CASTLE_COMPONENTS_COLLISION_COMPONENT_HPP_
#define INCLUDED_CASTLE_COMPONENTS_COLLISION_COMPONENT_HPP_

#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/Component.hpp>

#include <Castle/Components/PositionComponent.hpp>

#include <functional>

namespace castle {
	
	struct CollisionComponent : ecs::Component {
		PositionComponent *position{ nullptr };
		sf::Vector2f size;
		sf::Vector2f velocity;
		std::function<void(CollisionComponent&, CollisionComponent&)> callback{ nullptr };
		float collisionThreshold{ 0.5f };
		bool canCollide{ true };
		bool impactsMovement{ false };
		bool canBeMovedByOthers{ false };
		bool canMoveOthers{ false };
		bool effectedByGravity{ true };
		bool collidedRight{ false };
		bool collidedLeft{ false };
		bool collidedBottom{ false };
		bool collidedTop{ false };
		bool movedRight{ false };
		bool movedLeft{ false };
		bool movedUp{ false };
		bool movedDown{ false };
		bool wantsToFallThrough{ false };
		bool isOneWay{ false };

		bool isClimeable{ false }; // is a climeable ladder
		bool climbUp{ false };
		bool climbDown{ false };

		bool isOnClimbable{ false };
		bool isStillOnClimbable{ false };


		CollisionComponent(const sf::Vector2f& _size) :
			size(_size) {
			
		}

		void init(void) override {
			position = &entity->getComponent<PositionComponent>();
		}

		/*
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override {
			const sf::RectangleShape r(size);
			_states.transform.translate(position->position - sf::Vector2f(size.x / 2.0f, size.y));
			_target.draw(r, _states);
		}
		*/

	};

}

#endif // INCLUDED_CASTLE_COMPONENTS_COLLISION_COMPONENT_HPP_