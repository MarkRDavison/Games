#include <Castle/Systems/PlayerControlSystem.hpp>
#include <Castle/Components/PlayerComponent.hpp>
#include <Castle/Components/SpriteComponent.hpp>
#include <Castle/Components/CollisionComponent.hpp>

namespace castle {

	PlayerControlSystem::PlayerControlSystem(EntityGroup _group, inf::InputManager& _inputManager) :
		m_Group(_group),
		m_InputManager(_inputManager) {
		
	}

	void PlayerControlSystem::update(float _delta, ecs::EntityManager& _entityManager) {
		for (ecs::Entity *e : _entityManager.getEntitiesByGroup(m_Group)) {
			updateEntity(e, _delta);
		}
	}
	bool PlayerControlSystem::handleEvent(const sf::Event& _event, ecs::EntityManager& _entityManager) {
		return false;
	}

	void PlayerControlSystem::updateEntity(ecs::Entity* _entity, float _delta) const {
		auto& player = _entity->getComponent<PlayerComponent>();
		auto& sprite = _entity->getComponent<SpriteComponent>();
		auto& col = _entity->getComponent<CollisionComponent>();
		
		col.velocity.x = 0.0f;
		if (col.isOnClimbable) {
			col.velocity.y = 0.0f;
		}

		const sf::Keyboard::Key climbUpKey = sf::Keyboard::W;
		const sf::Keyboard::Key climbDownKey = sf::Keyboard::S;

		if (col.isOnClimbable && m_InputManager.isKeyPressed(climbUpKey)) {
			col.velocity.y = -PlayerComponent::VerticalVelocity; // TODO: Extract out gravity versus impulse velocity, so that you dont hop off of a ladder
		}
		if (col.isOnClimbable && m_InputManager.isKeyPressed(climbDownKey)) {
			col.velocity.y = +PlayerComponent::VerticalVelocity;
		}
		if (m_InputManager.isKeyPressed(sf::Keyboard::A)) {
			col.velocity.x -= PlayerComponent::HorizontalVelocity;
			player.facingRight = false;
		}
		if (m_InputManager.isKeyPressed(sf::Keyboard::D)) {
			col.velocity.x += PlayerComponent::HorizontalVelocity;
			player.facingRight = true;
		}
		if (m_InputManager.isKeyPressed(sf::Keyboard::LControl)) {
			if (!player.interacting && !player.interactingLock) {
				player.interacting = true;
			}
		} else {
			player.interactingLock = false;
		}
		sprite.flipHorizontal = !player.facingRight;
		if (player.jumpLocked && !m_InputManager.isKeyPressed(sf::Keyboard::Space)) {
			player.jumpLocked = false;
		}
		if (!col.isOnClimbable && !player.jumpLocked && player.onGround && m_InputManager.isKeyPressed(sf::Keyboard::Space)) {
			if (player.jumpLeft > 0) {
				player.jumpLeft--;
				player.jumpLocked = true;
				player.onGround = false;
				col.velocity.y = PlayerComponent::JumpVelocity;
			}
		}
		col.climbUp = m_InputManager.isKeyPressed(climbUpKey);
		col.climbDown = m_InputManager.isKeyPressed(climbDownKey);
		col.wantsToFallThrough = m_InputManager.isKeyPressed(sf::Keyboard::S);
	}

}
