#ifndef INCLUDED_PACMAN_COMPONENTS_GHOST_ANIMATION_COMPONENT_HPP_
#define INCLUDED_PACMAN_COMPONENTS_GHOST_ANIMATION_COMPONENT_HPP_

#include <Pacman/Components/SpriteComponent.hpp>

#include <Pacman/Infrastructure/Definitions.hpp>

#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/Component.hpp>

#include <vector>
#include <map>

namespace pacman {
	struct GhostAnimationComponent : ecs::Component {

		enum class GhostAnimation {
			MoveLeft,
			MoveRight,
			MoveUp,
			MoveDown,
			EyeLeft,
			EyeRight,
			EyeUp,
			EyeDown,
			Afraid
		};

		SpriteComponent *sprite{ nullptr };
		GhostAnimation currentAnimation;
		GhostType ghostType;
		std::size_t currentAnimationFrame{ 0u };
		float dieAccumulator{ 0.0f };
		float movementAccumulator{ 0.0f };
		float afraidAccumulator{ 0.0f };
		const float DieAnimationLimit{ 0.25f };
		const float MovementAnimationLimit{ 0.125f };
		const float AfraidAnimationLimit{ 0.125f };
		bool isDead{ false };
		bool isAfraid{ false };

		std::map<GhostType, std::map<GhostAnimation, std::vector<SpriteFrame>>> animationFrameMap;

		GhostAnimationComponent(GhostType _type) :
			GhostAnimationComponent(GhostAnimation::MoveUp, _type) {
		}


		GhostAnimationComponent(GhostAnimation _animation, GhostType _type) :
			currentAnimation(_animation),
			ghostType(_type) {

			switch (_type) {
			case GhostType::Blue:
				emplaceGhostData(GhostType::Blue, { 192.0f, 192.0f });
				break;
			case GhostType::Red:
				emplaceGhostData(GhostType::Red, { 0.0f, 144.0f });
				break;
			case GhostType::Pink:
				emplaceGhostData(GhostType::Pink, { 0.0f, 192.0f });
				break;
			case GhostType::Yellow:
				emplaceGhostData(GhostType::Yellow, { 0.0f, 216.0f });
				break;
			}
		}

		void emplaceGhostData(GhostType _type, const sf::Vector2f& _startingPoint) {
			std::map<GhostAnimation, std::vector<SpriteFrame>> ghost;

			ghost.emplace(GhostAnimation::MoveLeft, std::vector<SpriteFrame>{
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(_startingPoint.x + 96.0f, _startingPoint.y, 24.0f, 24.0f)),
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(_startingPoint.x + 120.0f, _startingPoint.y, 24.0f, 24.0f))
				});
			ghost.emplace(GhostAnimation::MoveRight, std::vector<SpriteFrame>{
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(_startingPoint.x + 0.0f, _startingPoint.y, 24.0f, 24.0f)),
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(_startingPoint.x + 24.0f, _startingPoint.y, 24.0f, 24.0f))
				});
			ghost.emplace(GhostAnimation::MoveUp, std::vector<SpriteFrame>{
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(_startingPoint.x + 144.0f, _startingPoint.y, 24.0f, 24.0f)),
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(_startingPoint.x + 168.0f, _startingPoint.y, 24.0f, 24.0f))
				});
			ghost.emplace(GhostAnimation::MoveDown, std::vector<SpriteFrame>{
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(_startingPoint.x + 48.0f, _startingPoint.y, 24.0f, 24.0f)),
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(_startingPoint.x + 72.0f, _startingPoint.y, 24.0f, 24.0f))
				});

			ghost.emplace(GhostAnimation::EyeLeft, std::vector<SpriteFrame>{
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(192.0f + 96.0f, 216.0f, 24.0f, 24.0f)),
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(192.0f + 120.0f, 216.0f, 24.0f, 24.0f))
				});
			ghost.emplace(GhostAnimation::EyeRight, std::vector<SpriteFrame>{
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(192.0f + 0.0f, 216.0f, 24.0f, 24.0f)),
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(192.0f + 24.0f, 216.0f, 24.0f, 24.0f))
				});
			ghost.emplace(GhostAnimation::EyeUp, std::vector<SpriteFrame>{
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(192.0f + 144.0f, 216.0f, 24.0f, 24.0f)),
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(192.0f + 168.0f, 216.0f, 24.0f, 24.0f))
				});
			ghost.emplace(GhostAnimation::EyeDown, std::vector<SpriteFrame>{
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(192.0f + 48.0f, 216.0f, 24.0f, 24.0f)),
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(192.0f + 72.0f, 216.0f, 24.0f, 24.0f))
				});

			ghost.emplace(GhostAnimation::Afraid, std::vector<SpriteFrame>{
				SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(144.0f, 96.0f, 24.0f, 24.0f)),
					SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(168.0f, 96.0f, 24.0f, 24.0f)),
					SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(192.0f, 96.0f, 24.0f, 24.0f)),
					SpriteFrame(sf::Vector2f(1.0f, 1.0f), sf::FloatRect(216.0f, 96.0f, 24.0f, 24.0f)),
			});

			animationFrameMap.emplace(_type, ghost);
		}

		void init(void) override {
			sprite = &entity->getComponent<SpriteComponent>();

			sprite->setSpriteFrame(animationFrameMap[ghostType][currentAnimation][currentAnimationFrame]);
		}

		void updateDead(float _delta) {
			dieAccumulator += _delta;
			if (dieAccumulator >= DieAnimationLimit) {
				dieAccumulator -= DieAnimationLimit;
				++currentAnimationFrame;
				if (currentAnimationFrame >= animationFrameMap[ghostType][currentAnimation].size()) {
					currentAnimationFrame = 0;
				}
				sprite->setSpriteFrame(animationFrameMap[ghostType][currentAnimation][currentAnimationFrame]);
			}
		}

		void updateMove(float _delta) {
			movementAccumulator += _delta;
			if (movementAccumulator >= MovementAnimationLimit) {
				movementAccumulator -= MovementAnimationLimit;
				++currentAnimationFrame;
				if (currentAnimationFrame >= animationFrameMap[ghostType][currentAnimation].size()) {
					currentAnimationFrame = 0;
				}
				sprite->setSpriteFrame(animationFrameMap[ghostType][currentAnimation][currentAnimationFrame]);
			}

		}

		void updateAfraid(float _delta) {
			afraidAccumulator += _delta;
			if (afraidAccumulator >= AfraidAnimationLimit) {
				afraidAccumulator -= AfraidAnimationLimit;
				++currentAnimationFrame;
				if (currentAnimationFrame >= animationFrameMap[ghostType][currentAnimation].size()) {
					currentAnimationFrame = 0;
				}
				sprite->setSpriteFrame(animationFrameMap[ghostType][currentAnimation][currentAnimationFrame]);
			}

		}

		void update(float _delta) override {
			if (isDead) {
				switch (currentAnimation) {
				case GhostAnimation::MoveDown:
					currentAnimation = GhostAnimation::EyeDown;
					break;
				case GhostAnimation::MoveRight:
					currentAnimation = GhostAnimation::EyeRight;
					break;
				case GhostAnimation::MoveUp:
					currentAnimation = GhostAnimation::EyeUp;
					break;
				case GhostAnimation::MoveLeft:
					currentAnimation = GhostAnimation::EyeLeft;
					break;
				default:
					break;
				}
			} else {
				switch (currentAnimation) {
				case GhostAnimation::EyeDown:
					currentAnimation = GhostAnimation::MoveDown;
					break;
				case GhostAnimation::EyeRight:
					currentAnimation = GhostAnimation::MoveRight;
					break;
				case GhostAnimation::EyeUp:
					currentAnimation = GhostAnimation::MoveUp;
					break;
				case GhostAnimation::EyeLeft:
					currentAnimation = GhostAnimation::MoveLeft;
					break;
				default:
					break;
				}
			}
			switch (currentAnimation) {
			case GhostAnimation::EyeDown:
			case GhostAnimation::EyeLeft:
			case GhostAnimation::EyeRight:
			case GhostAnimation::EyeUp:
				updateDead(_delta);
				break;
			case GhostAnimation::MoveDown:
			case GhostAnimation::MoveRight:
			case GhostAnimation::MoveUp:
			case GhostAnimation::MoveLeft:
				updateMove(_delta);
				break;
			default:
				updateAfraid(_delta);
				break;
			}
		}

	};
}

#endif // INCLUDED_PACMAN_COMPONENTS_GHOST_ANIMATION_COMPONENT_HPP_