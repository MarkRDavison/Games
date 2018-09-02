#ifndef INCLUDED_HURRICANE_COMPONENTS_COLLISION_COMPONENT_HPP_
#define INCLUDED_HURRICANE_COMPONENTS_COLLISION_COMPONENT_HPP_

#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/Component.hpp>

#include <Hurricane/Components/PositionComponent.hpp>

namespace hur {
	struct CollisionComponent : ecs::Component {

		sf::Vector2f size;
		sf::Vector2f offset;
		PositionComponent *position{nullptr};
		
		CollisionComponent(const sf::Vector2f& _size) :
			CollisionComponent(_size, sf::Vector2f()) {
			
		}
		CollisionComponent(const sf::Vector2f& _size, const sf::Vector2f& _offset) :
			size(_size),
			offset(_offset) {

		}

		void init(void) override {
			position = &entity->getComponent<PositionComponent>();
		}

		sf::FloatRect getBounds(void) const {
			return sf::FloatRect(position->position + offset - sf::Vector2f(size.x / 2.0f, size.y), size);
		}

		/*void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override {
			_states.transform.translate(position->position + offset - sf::Vector2f(size.x / 2.0f, size.y));

			sf::RectangleShape r(size);
			r.setFillColor(sf::Color::Transparent);
			r.setOutlineColor(sf::Color::White);
			r.setOutlineThickness(0.05f);
			
			_target.draw(r, _states);
		}*/
	};
}

#endif // INCLUDED_HURRICANE_COMPONENTS_COLLISION_COMPONENT_HPP_