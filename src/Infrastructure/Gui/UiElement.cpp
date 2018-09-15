#include <Infrastructure/Gui/UiElement.hpp>
#include <iostream>

namespace inf {

	UiElement::UiElement(const std::string& _elementName) :
		m_Name(_elementName) {
		
	}
	UiElement::~UiElement(void) {
		
	}

	void UiElement::update(float _delta) {
		
	}
	bool UiElement::handleEvent(const sf::Event& _event, bool& _handled) {
		if (_event.type == sf::Event::MouseButtonPressed ||
			_event.type == sf::Event::MouseButtonReleased) {
			if (handleMouseButtonPressed(_event)) {
				return true;
			}
		}
		if (_event.type == sf::Event::MouseMoved) {
			if (handleMouseMoved(_event)) {
				return true;
			}
		}
		return false;
	}

	void UiElement::setEnabled(bool _enabled) {
		m_Enabled = _enabled;
		onEnabledChanged(m_Enabled);
		if (!m_Enabled) {
			setFocus(false);
		}
	}

	void UiElement::setFocus(bool _focus) {
		m_HasFocus = _focus;
		onHasFocusChanged(m_HasFocus);
	}

	bool UiElement::handleMouseButtonPressed(const sf::Event& _event) {
		const sf::FloatRect& bounds = getBounds();

		const sf::Vector2f& mousePosition = sf::Vector2f(_event.mouseButton.x, _event.mouseButton.y);

		const bool contained = bounds.contains(mousePosition);

		bool result = false;

		if (m_MouseContained != contained) {
			m_MouseContained = contained;
			result = true;
		}

		if (m_MousePressedWithinBounds != sf::Mouse::isButtonPressed(_event.mouseButton.button)) {
			if (contained) {
				m_MousePressedWithinBounds = sf::Mouse::isButtonPressed(_event.mouseButton.button);
				onClickWithinBounds(_event.mouseButton.button, m_MousePressedWithinBounds);
			} else {
				if (!sf::Mouse::isButtonPressed(_event.mouseButton.button)) {
					m_MousePressedWithinBounds = false;
					onClickOutsideBounds(_event.mouseButton.button, m_MousePressedWithinBounds);
				}
			}
			result = true;
		} else {
			if (m_HasFocus) {
				onClickOutsideBounds(_event.mouseButton.button, m_MousePressedWithinBounds);
				result = true;
			}
		}

		return result;
	}

	bool UiElement::handleMouseMoved(const sf::Event& _event) {
		const sf::FloatRect& bounds = getBounds();

		const sf::Vector2f& mousePosition = sf::Vector2f(_event.mouseMove.x, _event.mouseMove.y);

		const bool contained = bounds.contains(mousePosition);

		bool result = false;

		if (m_MouseContained != contained) {
			m_MouseContained = contained;
			result = true;
		}

		return result;
	}
}
