#include <Castle/Systems/PlayerInteractionSystem.hpp>
#include <Castle/Infrastructure/EntityGroups.hpp>
#include <Castle/Components/PlayerComponent.hpp>
#include <Castle/Components/PositionComponent.hpp>
#include <Castle/Components/TimerComponent.hpp>
#include <Castle/Components/RectangleComponent.hpp>
#include <Castle/Components/InteractableComponent.hpp>
#include <iostream>
#include <Castle/Components/CollisionComponent.hpp>

namespace castle {

	PlayerInteractionSystem::PlayerInteractionSystem(void)  {
		
	}

	void PlayerInteractionSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (ecs::Entity *e : _entityManager.getEntitiesByGroup(castle::EntityGroup::GPlayer)) {
			updateEntity(e, _delta, _entityManager);
		}
	}
	bool PlayerInteractionSystem::handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) {
		return false;
	}

	void PlayerInteractionSystem::updateEntity(ecs::Entity* _entity, float _delta, ecs::EntityManager& _entityManager) const {
		auto& player = _entity->getComponent<PlayerComponent>();
		auto& position = _entity->getComponent<PositionComponent>();
		auto& collision = _entity->getComponent<CollisionComponent>();
		if (player.interacting) {
			player.interactingLock = true;
			player.interacting = false;

			const sf::Vector2f pos = position.position + (player.facingRight ? sf::Vector2f(1.0f, 0.0f) : sf::Vector2f(-1.0f, 0.0f));
			const sf::FloatRect playerInteractionBounds(pos - sf::Vector2f(collision.size.x / 2.0f, collision.size.y), collision.size);
			createPlayerInteractionOutlineEntity(pos, collision.size, 0.8f, _entityManager);

			for (ecs::Entity *e : _entityManager.getEntitiesByGroup(castle::EntityGroup::GInteractable)) {
				InteractableComponent& component = e->getComponent<InteractableComponent>();
				sf::FloatRect interactionBounds;
				sf::FloatRect interactableComponentBounds = component.bounds;
				if (interactableComponentBounds.intersects(playerInteractionBounds, interactionBounds)) {
					const float minX = std::min(playerInteractionBounds.width, interactableComponentBounds.width);
					const float minY = std::min(playerInteractionBounds.height, interactableComponentBounds.height);

					const float num = interactionBounds.width * interactionBounds.height;
					const float den = minX * minY;

					if (num / den > component.interactionRatio) {
						std::cout << "Interacted " << num << " / " << den << " = " << num / den << std::endl;
						if (component.interactCallback) {
							component.interactCallback(component.entity, _entity);
						}
					}
				}
			}
		}
	}

	void PlayerInteractionSystem::createPlayerInteractionOutlineEntity(const sf::Vector2f& _position, const sf::Vector2f& _size, float _duration, ecs::EntityManager& _entityManager) const {
		ecs::Entity& e = _entityManager.addEntity();
		e.addComponent<PositionComponent>(_position - sf::Vector2f(0.0f, 0.0f));
		e.addComponent<TimerComponent>(_duration);
		e.addComponent<RectangleComponent>(0.05f, _size, sf::Color::Yellow);
	}
}
