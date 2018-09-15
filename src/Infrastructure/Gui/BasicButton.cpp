#include <Infrastructure/Gui/BasicButton.hpp>
#include <Utility/Colour.hpp>
#include <iostream>

namespace inf {

	BasicButton::BasicButton(const std::string& _name) :
		UiElement(_name) {
		
		m_Bounds.setOutlineThickness(2.0f);
		onVisualChanged();
	}
	BasicButton::~BasicButton(void) {
		
	}

	bool BasicButton::handleEvent(const sf::Event& _event, bool& _handled) {
		if (!m_Enabled) {
			return false;
		}
		if (UiElement::handleEvent(_event, _handled)) {
			onVisualChanged();
		}
		if (_handled) {
			return true;
		}
		return false;
	}
	void BasicButton::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
		_states.transform.combine(getTransform());
		_target.draw(m_Bounds, _states);
	}

	sf::FloatRect BasicButton::getBounds(void) {
		sf::FloatRect bounds = m_Bounds.getGlobalBounds();
		bounds.left += getPosition().x;
		bounds.top += getPosition().y;
		return bounds;
	}

	void BasicButton::setSize(const sf::Vector2f& _size) {
		m_Bounds.setSize(_size);
	}
	void BasicButton::setCallback(std::function<void(bool)> _callback) {
		m_Callback = _callback;
	}

	void BasicButton::onClickWithinBounds(sf::Mouse::Button _button, bool _pressed)  {
		if (m_MouseContained) {
			if (m_Callback) {
				m_Callback(_pressed);
			}
			else {
				std::cout << "'" << getName() << "' button has been pressed and has no other callback, pressed: " << _pressed << std::endl;
			}
		}
	}

	void BasicButton::onEnabledChanged(bool _enabled) {
		onVisualChanged();
	}

	void BasicButton::setColour(const sf::Color& _color, ButtonColor _colorType) {
		switch (_colorType) {
		case ButtonColor::OutlineHovered: 
			m_OutlineHovered = _color;
			break;
		case ButtonColor::OutlineNormal: 
			m_OutlineNormal = _color;
			break;
		case ButtonColor::OutlinePressed:
			m_OutlinePressed = _color;
			break;
		case ButtonColor::OutlineDisabled:
			m_OutlineDisabled = _color;
			break;
		case ButtonColor::InnerHovered:
			m_InnerHovered = _color;
			break;
		case ButtonColor::InnerNormal:
			m_InnerNormal = _color;
			break;
		case ButtonColor::InnerPressed:
			m_InnerPressed = _color;
			break;
		case ButtonColor::InnerDisabled:
			m_InnerDisabled = _color;
			break;
		}
		onVisualChanged();
	}

	void BasicButton::onVisualChanged(void) {
		sf::Color internalColor;
		sf::Color outlineColor;

		if (m_Enabled) {
			if (m_MousePressedWithinBounds) {
				internalColor = m_InnerHovered;
				outlineColor = m_OutlineHovered;
			} else if (m_MouseContained) {
				internalColor = m_InnerPressed;
				outlineColor = m_OutlinePressed;
			} else {
				internalColor = m_InnerNormal;
				outlineColor = m_OutlineNormal;
			}
		} else {
			internalColor = m_InnerDisabled;
			outlineColor = m_OutlineDisabled;
		}

		m_Bounds.setOutlineColor(outlineColor);
		m_Bounds.setFillColor(internalColor);
	}

}
