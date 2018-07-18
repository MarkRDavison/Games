#ifndef INCLUDED_CASTLE_COMPONENTS_INTERACTABLE_COMPONENT_HPP_
#define INCLUDED_CASTLE_COMPONENTS_INTERACTABLE_COMPONENT_HPP_

#include <Castle/Components/PositionComponent.hpp>
#include <EntityComponentSystem/Entity.hpp>

#include <functional>

namespace castle {
	
	struct InteractableComponent : ecs::Component {
		PositionComponent *position{ nullptr };
		std::function<void(ecs::Entity *, ecs::Entity *)> interactCallback{nullptr};
		sf::Vector2f size;
		sf::FloatRect bounds;
		float interactionRatio{ 0.6f };

		InteractableComponent(const sf::Vector2f& _size) :
			size(_size) {

		}
		InteractableComponent(const sf::Vector2f& _size, std::function<void(ecs::Entity *, ecs::Entity *)> _callback) :
			size(_size),
			interactCallback(_callback) {

		}

		void init(void) override {
			position = &entity->getComponent<PositionComponent>();
			bounds = sf::FloatRect(position->position.x - size.x / 2.0f, position->position.y - size.y, size.x, size.y);
		}

	};

}

#endif // INCLUDED_CASTLE_COMPONENTS_INTERACTABLE_COMPONENT_HPP_