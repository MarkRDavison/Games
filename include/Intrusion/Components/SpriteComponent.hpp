#ifndef INCLUDED_INTRUSION_COMPONENTS_SPRITE_COMPONENT_HPP_
#define INCLUDED_INTRUSION_COMPONENTS_SPRITE_COMPONENT_HPP_

#include <Intrusion/Components/RenderableComponent.hpp>

namespace itr {

	struct SpriteComponent : RenderableComponent {
		sf::Sprite sprite;
		sf::Vector2f visualOffset;
		bool flipHorizontal{ true };
		bool flipVertical{ false };
		bool toRender{ true };
		float scale;

		SpriteComponent(const sf::Texture& _texture, const sf::IntRect& _textureBounds, float _scale) :
			sprite(_texture, _textureBounds),
			scale(_scale) {
			sprite.setOrigin(static_cast<float>(_textureBounds.width) / 2.0f, static_cast<float>(_textureBounds.height)); // Origin is bottom center?
			sprite.setScale(1.0f / _scale, 1.0f / _scale);
		}

		void render(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override {
			if (toRender) {
				_states.transform.translate(position->position + (position->position - position->previousPosition) * _alpha + visualOffset / scale);
				_states.transform.scale(flipHorizontal ? -1.0f : 1.0f, flipVertical ? -1.0f : 1.0f);
				_target.draw(sprite, _states);
			}
		}
	};

}

#endif // INCLUDED_INTRUSION_COMPONENTS_SPRITE_COMPONENT_HPP_