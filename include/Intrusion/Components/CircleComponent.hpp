#ifndef INCLUDED_INTRUSION_COMPONENTS_CIRCLE_COMPONENT_HPP_
#define INCLUDED_INTRUSION_COMPONENTS_CIRCLE_COMPONENT_HPP_

#include <Intrusion/Components/RenderableComponent.hpp>

namespace itr {

	struct CircleComponent : RenderableComponent {
		sf::CircleShape circle;
		sf::Vector2f visualOffset;
		bool toRender{ true };
		float scale;

		CircleComponent(float _radius, float _scale) :
			circle(_radius),
			scale(_scale) {
			circle.setOrigin(_radius, _radius);
			circle.setFillColor(sf::Color::Yellow);
		}

		void render(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override {
			if (toRender) {
				_states.transform.translate(position->position + (position->position - position->previousPosition) * _alpha + visualOffset / scale);
				_target.draw(circle, _states);
			}
		}
	};

}

#endif // INCLUDED_INTRUSION_COMPONENTS_CIRCLE_COMPONENT_HPP_