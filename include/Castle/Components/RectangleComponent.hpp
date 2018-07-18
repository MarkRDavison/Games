#ifndef INCLUDED_CASTLE_COMPONENTS_RECTANGLE_COMPONENT_HPP_
#define INCLUDED_CASTLE_COMPONENTS_RECTANGLE_COMPONENT_HPP_

#include <Castle/Components/PositionComponent.hpp>

#include <EntityComponentSystem/Entity.hpp>

namespace castle {
	
	struct RectangleComponent : ecs::Component {

		PositionComponent* position{ nullptr };
		sf::RectangleShape shape;
		sf::Vector2f size;
		sf::Color color{ sf::Color::Black };
		float outlineThickness{ 0.0f };
		bool outline{ false };

		RectangleComponent(float _outlineThickness, const sf::Vector2f& _size, const sf::Color& _color) :
			size{_size},
			color{_color},
			outlineThickness{ _outlineThickness },
			outline{ true } {
			
		}
		RectangleComponent(const sf::Vector2f& _size, const sf::Color& _color) : 
			size{ _size },
			color{_color},
			outline{ false } {

		}

		void init(void) override {
			position = &entity->getComponent<PositionComponent>();
			
			if (outline) {
				shape.setSize(size);
				shape.setFillColor(sf::Color::Transparent);
				shape.setOutlineColor(color);
				shape.setOutlineThickness(outlineThickness);
				shape.setOrigin(size.x / 2.f, size.y);
			}
			else {
				shape.setSize(size);
				shape.setFillColor(color);
				shape.setOrigin(size.x / 2.f, size.y);
			}
		}

		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override {
			_states.transform.translate(position->position);
			_target.draw(shape, _states);
		}
	};

}

#endif // INCLUDED_CASTLE_COMPONENTS_RECTANGLE_COMPONENT_HPP_