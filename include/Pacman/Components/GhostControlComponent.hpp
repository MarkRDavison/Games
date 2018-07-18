#ifndef INCLUDED_PACMAN_COMPONENTS_GHOST_CONTROL_COMPONENT_HPP_
#define INCLUDED_PACMAN_COMPONENTS_GHOST_CONTROL_COMPONENT_HPP_

#include <Pacman/Components/GhostAnimationComponent.hpp>

#include <EntityComponentSystem/Component.hpp>
#include <EntityComponentSystem/Entity.hpp>

namespace pacman {
	
	struct GhostControlComponent : ecs::Component {
		GhostAnimationComponent *animation{ nullptr };

		void init(void) override {
			animation = &entity->getComponent<GhostAnimationComponent>();
		}

		void update(float _delta) override {
			return;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				if (!animation->isAfraid) {
					if (animation->isDead) {
						animation->currentAnimation = GhostAnimationComponent::GhostAnimation::EyeUp;
					}
					else {
						animation->currentAnimation = GhostAnimationComponent::GhostAnimation::MoveUp;
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				if (!animation->isAfraid) {
					if (animation->isDead) {
						animation->currentAnimation = GhostAnimationComponent::GhostAnimation::EyeLeft;
					}
					else {
						animation->currentAnimation = GhostAnimationComponent::GhostAnimation::MoveLeft;
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				if (!animation->isAfraid) {
					if (animation->isDead) {
						animation->currentAnimation = GhostAnimationComponent::GhostAnimation::EyeDown;
					}
					else {
						animation->currentAnimation = GhostAnimationComponent::GhostAnimation::MoveDown;
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				if (!animation->isAfraid) {
					if (animation->isDead) {
						animation->currentAnimation = GhostAnimationComponent::GhostAnimation::EyeRight;
					}
					else {
						animation->currentAnimation = GhostAnimationComponent::GhostAnimation::MoveRight;
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				animation->isDead = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				animation->isDead = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
				animation->isAfraid = true;
				animation->currentAnimation = GhostAnimationComponent::GhostAnimation::Afraid;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
				animation->isAfraid = false;
				animation->currentAnimation = GhostAnimationComponent::GhostAnimation::MoveUp;
			}
		}
	};

}

#endif // INCLUDED_PACMAN_COMPONENTS_GHOST_CONTROL_COMPONENT_HPP_