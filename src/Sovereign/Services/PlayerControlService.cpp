#include <Sovereign/Services/PlayerControlService.hpp>

namespace sov {

	PlayerControlService::PlayerControlService(EntityData& _entityData, ControlBindings& _controlBindings) :
		m_EntityData(_entityData),
		m_ControlBindings(_controlBindings) {
		
	}

	PlayerControlService::~PlayerControlService(void) {
		
	}

	bool PlayerControlService::handleEvent(const sf::Event& _event) const {
		switch (_event.type) {
		case sf::Event::KeyPressed:
		case sf::Event::KeyReleased:
			return handleKeyEvent(_event);
		default:
			return false;
		}
	}

	bool PlayerControlService::handleKeyEvent(const sf::Event& _keyEvent) const {
		if (_keyEvent.key.code == m_ControlBindings.moveLeftBinding) {
			for (MoveableEntity& me : m_EntityData.moveableEntities) {
				if (me.isPlayer) {
					me.moveLeft = _keyEvent.type == sf::Event::KeyPressed;
				}
			}
			return true;
		}
		if (_keyEvent.key.code == m_ControlBindings.moveRightBinding) {
			for (MoveableEntity& me : m_EntityData.moveableEntities) {
				if (me.isPlayer) {
					me.moveRight = _keyEvent.type == sf::Event::KeyPressed;
				}
			}
			return true;
		}
		if (_keyEvent.key.code == m_ControlBindings.moveUpBinding) {
			for (MoveableEntity& me : m_EntityData.moveableEntities) {
				if (me.isPlayer) {
					me.moveUp = _keyEvent.type == sf::Event::KeyPressed;
				}
			}
			return true;
		}
		if (_keyEvent.key.code == m_ControlBindings.moveDownBinding) {
			for (MoveableEntity& me : m_EntityData.moveableEntities) {
				if (me.isPlayer) {
					me.moveDown = _keyEvent.type == sf::Event::KeyPressed;
				}
			}
			return true;
		}
		return false;
	}

}
