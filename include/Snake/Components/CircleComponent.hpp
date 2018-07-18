#ifndef INCLUDED_SNAKE_COMPONENTS_CIRCLE_COMPONENT_HPP_
#define INCLUDED_SNAKE_COMPONENTS_CIRCLE_COMPONENT_HPP_

#include <Snake/Components/PositionComponent.hpp>

#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/Component.hpp>

namespace snake {
	struct CircleComponent : ecs::Component {
		PositionComponent* cPosition{ nullptr };
		sf::CircleShape shape;
		float radius;

		CircleComponent(float mRadius) : radius{ mRadius } {

		}

		void init() override {
			cPosition = &entity->getComponent<PositionComponent>();

			shape.setRadius(radius);
			shape.setFillColor(sf::Color::Red);
			shape.setOrigin(radius, radius);
		}

		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override {
			_states.transform.translate(cPosition->position);
			_target.draw(shape, _states);
		}
	};
}

#endif // INCLUDED_SNAKE_COMPONENTS_CIRCLE_COMPONENT_HPP_