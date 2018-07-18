#ifndef INCLUDED_ARKANOID_COMPONENTS_PHYSICS_COMPONENT_HPP_
#define INCLUDED_ARKANOID_COMPONENTS_PHYSICS_COMPONENT_HPP_

#include <Arkanoid/Components/PositionComponent.hpp>
#include <Arkanoid/Infrastructure/Definitions.hpp>

#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/Component.hpp>

#include <functional>

namespace ark {
	struct PhysicsComponent : ecs::Component {
		PhysicsComponent(const sf::Vector2f& mHalfSize) : halfSize{ mHalfSize } {}

		void init() override 		{
			cPosition = &entity->getComponent<PositionComponent>();
		}

		void update(float _delta) override {
			cPosition->position += velocity * _delta;

			if (onOutOfBounds == nullptr) return;

			if (left() < 0) {
				onOutOfBounds(sf::Vector2f{ 1.f, 0.f });
			}
			else if (right() > Definitions::WindowWidth) {
				onOutOfBounds(sf::Vector2f{ -1.f, 0.f });
			}
			if (top() < 0) {
				onOutOfBounds(sf::Vector2f{ 0.f, 1.f });
			}
			else if (bottom() > Definitions::WindowHeight) {
				onOutOfBounds(sf::Vector2f{ 0.f, -1.f });
			}
		}

		float x() const noexcept { return cPosition->x(); }
		float y() const noexcept { return cPosition->y(); }
		float left() const noexcept { return x() - halfSize.x; }
		float right() const noexcept { return x() + halfSize.x; }
		float top() const noexcept { return y() - halfSize.y; }
		float bottom() const noexcept { return y() + halfSize.y; }

		PositionComponent* cPosition{ nullptr };
		sf::Vector2f velocity, halfSize;

		// We will use a callback to handle the "out of bounds" event.
		std::function<void(const sf::Vector2f&)> onOutOfBounds;
	};
}

#endif // INCLUDED_ARKANOID_COMPONENTS_PHYSICS_COMPONENT_HPP_