#ifndef INCLUDED_PACMAN_COMPONENTS_SPRITE_COMPONENT_HPP_
#define INCLUDED_PACMAN_COMPONENTS_SPRITE_COMPONENT_HPP_

#include <Pacman/Components/PositionComponent.hpp>

#include <EntityComponentSystem/Component.hpp>
#include <EntityComponentSystem/Entity.hpp>

namespace pacman {

	struct SpriteFrame {
		SpriteFrame(const sf::Vector2f& _size, const sf::FloatRect& _textureCoordinates) :
			size(_size),
			textureCoordinates(_textureCoordinates) {
			
		}

		sf::Vector2f size;
		sf::FloatRect textureCoordinates;		
	};

	struct SpriteComponent : ecs::Component {
		PositionComponent *position{nullptr};
		const sf::Texture& texture;
		sf::VertexArray vertexArray{ sf::Triangles };

		SpriteComponent(const sf::Texture& _texture) :
			texture(_texture) {
			
		}

		~SpriteComponent(void) override {
			
		}

		void init(void) override {
			position = &entity->getComponent<PositionComponent>();
		}
		
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override {
			_states.texture = &texture;
			_states.transform.translate(position->position);
			_target.draw(vertexArray, _states);
		}

		void setSpriteFrame(const SpriteFrame& _frame) {
			vertexArray.clear();

			vertexArray.append(sf::Vertex({ -_frame.size.x / 2.0f, -_frame.size.y / 2.0f }, { _frame.textureCoordinates.left, _frame.textureCoordinates.top }));
			vertexArray.append(sf::Vertex({ +_frame.size.x / 2.0f, -_frame.size.y / 2.0f }, { _frame.textureCoordinates.left + _frame.textureCoordinates.width, _frame.textureCoordinates.top }));
			vertexArray.append(sf::Vertex({ +_frame.size.x / 2.0f, +_frame.size.y / 2.0f }, { _frame.textureCoordinates.left + _frame.textureCoordinates.width, _frame.textureCoordinates.top + _frame.textureCoordinates.height }));

			vertexArray.append(sf::Vertex({ -_frame.size.x / 2.0f, -_frame.size.y / 2.0f }, { _frame.textureCoordinates.left, _frame.textureCoordinates.top }));
			vertexArray.append(sf::Vertex({ +_frame.size.x / 2.0f, +_frame.size.y / 2.0f }, { _frame.textureCoordinates.left + _frame.textureCoordinates.width, _frame.textureCoordinates.top + _frame.textureCoordinates.height }));
			vertexArray.append(sf::Vertex({ -_frame.size.x / 2.0f, +_frame.size.y / 2.0f }, { _frame.textureCoordinates.left, _frame.textureCoordinates.top + _frame.textureCoordinates.height }));
		}
	};

}

#endif // INCLUDED_PACMAN_COMPONENTS_SPRITE_COMPONENT_HPP_