#ifndef INCLUDED_ARKANOID_COMPONENTS_RECTANGLE_COMPONENT_HPP_
#define INCLUDED_ARKANOID_COMPONENTS_RECTANGLE_COMPONENT_HPP_

#include <Arkanoid/Components/PositionComponent.hpp>

#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/Component.hpp>

namespace ark {

	struct RectangleComponent : ecs::Component {

		PositionComponent* cPosition{ nullptr }; 
		sf::RectangleShape shape;
		sf::Vector2f size;

		RectangleComponent(const sf::Vector2f& mHalfSize) : size{ mHalfSize * 2.f }  {

		}

		void init() override {
			cPosition = &entity->getComponent<PositionComponent>();


			shape.setSize(size);
			shape.setFillColor(sf::Color::Red);
			shape.setOrigin(size.x / 2.f, size.y / 2.f);
		}

		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override {
			_states.transform.translate(cPosition->position);
			_target.draw(shape, _states);
		}
	};

}

#endif // INCLUDED_ARKANOID_COMPONENTS_RECTANGLE_COMPONENT_HPP_