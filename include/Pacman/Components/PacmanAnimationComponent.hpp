#ifndef INCLUDED_PACMAN_COMPONENTS_PACMAN_ANIMATION_COMPONENT_HPP_
#define INCLUDED_PACMAN_COMPONENTS_PACMAN_ANIMATION_COMPONENT_HPP_

#include <Pacman/Components/SpriteComponent.hpp>

#include <EntityComponentSystem/Component.hpp>
#include <EntityComponentSystem/Entity.hpp>

namespace pacman {
	struct PacmanAnimationComponent : ecs::Component {

		enum class PacmanAnimation {
			MoveLeft,
			MoveRight,
			MoveUp,
			MoveDown,
			Die
		};

		SpriteComponent *sprite{ nullptr };
		PacmanAnimation currentAnimation;
		std::size_t currentAnimationFrame{0u};
		bool moving{false};
		float dieAccumulator{ 0.0f };
		float movementAccumulator{ 0.0f };
		const float DieAnimationLimit{ 0.25f };
		const float MovementAnimationLimit{ 0.125f };

		std::map<PacmanAnimation, std::vector<SpriteFrame>> animationFrameMap;

		PacmanAnimationComponent(void) :
			PacmanAnimationComponent(PacmanAnimation::MoveUp) {
			
		}
		PacmanAnimationComponent(PacmanAnimation _animation) :
			currentAnimation(_animation) {

			animationFrameMap.insert({ PacmanAnimation::MoveLeft, {
				SpriteFrame({ 1.0f, 1.0f },{ 0.0f, 168.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 48.0f, 72.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 0.0f,  72.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 48.0f, 72.0f, 24.0f, 24.0f }),
			} });
			animationFrameMap.insert({ PacmanAnimation::MoveRight, {
				SpriteFrame({ 1.0f, 1.0f },{ 0.0f,  168.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 144.0f, 72.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 96.0f,  72.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 144.0f, 72.0f, 24.0f, 24.0f })
			} });
			animationFrameMap.insert({ PacmanAnimation::MoveUp, {
				SpriteFrame({ 1.0f, 1.0f },{ 0.0f, 168.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 72.0f, 72.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 24.0f, 72.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 72.0f, 72.0f, 24.0f, 24.0f }),
			} });
			animationFrameMap.insert({ PacmanAnimation::MoveDown, {
				SpriteFrame({ 1.0f, 1.0f },{ 0.0f,  168.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 168.0f, 72.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 120.0f, 72.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 168.0f, 72.0f, 24.0f, 24.0f })
			} });
			animationFrameMap.insert({ PacmanAnimation::Die, {
				SpriteFrame({ 1.0f, 1.0f },{ 0.0f, 168.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 72.0f, 72.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 24.0f, 72.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 96.0f,168.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 120.0f,168.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 144.0f,168.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 168.0f,168.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 192.0f,168.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 216.0f,168.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 240.0f,168.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 264.0f,168.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 288.0f,168.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 312.0f,168.0f, 24.0f, 24.0f }),
				SpriteFrame({ 1.0f, 1.0f },{ 336.0f,168.0f, 24.0f, 24.0f }),
			} });
		}
		
		void init(void) override {
			sprite = &entity->getComponent<SpriteComponent>();

			sprite->setSpriteFrame(animationFrameMap[currentAnimation][currentAnimationFrame]);
		}

		void updateDie(float _delta) {
			dieAccumulator += _delta;
			if (dieAccumulator >= DieAnimationLimit) {
				dieAccumulator -= DieAnimationLimit;
				++currentAnimationFrame;
				if (currentAnimationFrame >= animationFrameMap[currentAnimation].size()) {
					currentAnimationFrame = 0;
					entity->destroy();
				}
				sprite->setSpriteFrame(animationFrameMap[currentAnimation][currentAnimationFrame]);
			}
		}

		void updateMove(float _delta) {
			if (moving) {
				movementAccumulator += _delta;
				if (movementAccumulator >= MovementAnimationLimit) {
					movementAccumulator -= MovementAnimationLimit;
					++currentAnimationFrame;
					if (currentAnimationFrame >= animationFrameMap[currentAnimation].size()) {
						currentAnimationFrame = 0;
					}
					sprite->setSpriteFrame(animationFrameMap[currentAnimation][currentAnimationFrame]);
				}
			}
			
		}

		void update(float _delta) override {
			switch (currentAnimation) {
			case PacmanAnimation::Die:
				updateDie(_delta);
				break;
			default:
				updateMove(_delta);
				break;
			}
		}

	};
}

#endif // INCLUDED_PACMAN_COMPONENTS_PACMAN_ANIMATION_COMPONENT_HPP_