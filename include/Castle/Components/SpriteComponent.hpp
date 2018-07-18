#ifndef INCLUDED_CASTLE_COMPONENTS_SPRITE_COMPONENT_HPP_
#define INCLUDED_CASTLE_COMPONENTS_SPRITE_COMPONENT_HPP_

#include <Castle/Components/PositionComponent.hpp>
#include <EntityComponentSystem/Entity.hpp>

namespace castle {
	
	struct SpriteComponent : ecs::Component {
		PositionComponent *position{nullptr};
		sf::Sprite sprite;
		bool flipHorizontal{ true };
		bool flipVertical{ false };
		bool render{ true };

		SpriteComponent(const sf::Texture& _texture, const sf::IntRect& _textureBounds) :
			sprite(_texture, _textureBounds) {
			sprite.setOrigin(static_cast<float>(_textureBounds.width) / 2.0f, static_cast<float>(_textureBounds.height)); // Origin is bottom center?
			sprite.setScale(1.0f / 32.0f, 1.0f / 32.0f);
		}

		void init(void) override {
			position = &entity->getComponent<PositionComponent>();
		}

		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override {
			if (render) {
				_states.transform.translate(position->position);
				_states.transform.scale(flipHorizontal ? -1.0f : 1.0f, flipVertical ? -1.0f : 1.0f);
				_target.draw(sprite, _states);
			}
		}
	};

}

#endif // INCLUDED_CASTLE_COMPONENTS_SPRITE_COMPONENT_HPP_