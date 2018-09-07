#include <Infrastructure/Gui/UiElement.hpp>

namespace inf {

	UiElement::UiElement(const std::string& _elementName) :
		m_Name(_elementName) {
		
	}
	UiElement::~UiElement(void) {
		
	}

	void UiElement::update(float _delta) {
		
	}
	bool UiElement::handleEvent(const sf::Event& _event) {
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

		if (m_MousePressed != sf::Mouse::isButtonPressed(_event.mouseButton.button)) {
			if (contained) {
				m_MousePressed = sf::Mouse::isButtonPressed(_event.mouseButton.button);
				onClick(_event.mouseButton.button, m_MousePressed);
			}
			result = true;
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

		if (!contained && m_MousePressed) {
			m_MousePressed = false;
			result = true;
		}

		return result;
	}
}
