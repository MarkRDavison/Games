#ifndef INCLUDED_ARKANOID_COMPONENTS_PLAYER_PADDLE_CONTROL_COMPONENT_HPP_
#define INCLUDED_ARKANOID_COMPONENTS_PLAYER_PADDLE_CONTROL_COMPONENT_HPP_

#include <Arkanoid/Components/PhysicsComponent.hpp>
#include <Arkanoid/Infrastructure/Definitions.hpp>

#include <EntityComponentSystem/Component.hpp>

namespace ark {

	struct PlayerPaddleControlComponent : ecs::Component {

		PhysicsComponent* cPhysics{ nullptr };

		void init() override {
			cPhysics = &entity->getComponent<PhysicsComponent>();
		}

		void update(float _delta) override {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && cPhysics->left() > 0) {
				cPhysics->velocity.x = -Definitions::PaddleVelocity;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && cPhysics->right() < Definitions::WindowWidth) {
				cPhysics->velocity.x = Definitions::PaddleVelocity;
			}
			else {
				cPhysics->velocity.x = 0;
			}
		}
	};

}

#endif // INCLUDED_ARKANOID_COMPONENTS_PLAYER_PADDLE_CONTROL_COMPONENT_HPP_