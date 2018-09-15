#include <Infrastructure/Gui/TextBox.hpp>
#include <string>
#include <iostream>

namespace inf {
	
	TextBox::TextBox(const std::string& _name) :
		UiElement(_name) {
		
		m_Bounds.setOutlineThickness(2.0f);
		onVisualChanged();
	}
	TextBox::~TextBox(void) {

	}

	void TextBox::update(float _delta) {

	}
	bool TextBox::handleEvent(const sf::Event& _event, bool& _handled) {
		if (!m_Enabled) {
			return false;
		}
		if (UiElement::handleEvent(_event, _handled)) {
			onVisualChanged();
		}

		if (!_handled && _event.type == sf::Event::TextEntered) {
			handleTextEnteredEvent(_event, _handled);
		}

		if (!_handled && _event.type == sf::Event::KeyPressed) {
			handleKeyPressedEvent(_event, _handled);
		}

		if (_handled) {
			m_Text.setString(m_CurrentText);
		}

		return _handled;
	}
	void TextBox::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
		_states.transform.combine(getTransform());
		_target.draw(m_Bounds, _states);
		_target.draw(m_Text, _states);
	}

	sf::FloatRect TextBox::getBounds(void) {
		sf::FloatRect bounds = m_Bounds.getGlobalBounds();
		bounds.left += getPosition().x;
		bounds.top += getPosition().y;
		return bounds;
	}
	void TextBox::onEnabledChanged(bool _enabled) {
		onVisualChanged();
	}

	void TextBox::onHasFocusChanged(bool _hasFocus) {
		onVisualChanged();
	}

	void TextBox::onClickWithinBounds(sf::Mouse::Button _button, bool _pressed) {
		if (_button == sf::Mouse::Left && _pressed) {
			m_HasFocus = true;
			onVisualChanged();
		}
	}

	void TextBox::onClickOutsideBounds(sf::Mouse::Button _button, bool _pressed) {
		if (_button == sf::Mouse::Left) {
			m_HasFocus = false;
			onVisualChanged();
		}
	}

	void TextBox::setSize(const sf::Vector2f& _size) {
		m_Bounds.setSize(_size);
	}

	void TextBox::setColour(const sf::Color& _color, TextBoxColor _colorType) {
		switch (_colorType) {
		case TextBoxColor::OutlineNormal: 
			m_OutlineNormal = _color;
			break;
		case TextBoxColor::OutlineDisabled:
			m_OutlineDisabled = _color;
			break;
		case TextBoxColor::OutlineActive:
			m_OutlineActive = _color;
			break;
		case TextBoxColor::InnerNormal:
			m_InnerNormal = _color;
			break;
		case TextBoxColor::InnerDisabled:
			m_InnerDisabled = _color;
			break;
		case TextBoxColor::InnerActive:
			m_InnerActive = _color;
			break;
		case TextBoxColor::TextNormal:
			m_TextNormal = _color;
			break;
		case TextBoxColor::TextDisabled:
			m_TextDisabled = _color;
			break;
		case TextBoxColor::TextActive:
			m_TextActive = _color;
			break;
		}
	}

	void TextBox::setFont(const sf::Font& _font) {
		m_Text.setFont(_font);
	}
	void TextBox::setText(const std::string& _text) {
		m_CurrentText = _text;
		m_Text.setString(m_CurrentText);
	}

	void TextBox::handleTextEnteredEvent(const sf::Event& _event, bool& _handled) {
		if (getFocused()) {
			if (_event.text.unicode >= 32 && _event.text.unicode < 127) {
				const char c = static_cast<char>(_event.text.unicode);
				m_CurrentText += c;
				_handled = true;
			}
		}
	}
	void TextBox::handleKeyPressedEvent(const sf::Event& _event, bool& _handled) {
		if (getFocused()) {
			if (_event.key.code == sf::Keyboard::Key::BackSpace) {
				if (_event.key.control) {
					bool passedWhitespace = false;
					while (!m_CurrentText.empty()) {
						const bool whitespace = m_CurrentText.back() == ' ';
						if (whitespace && !passedWhitespace) {
							passedWhitespace = true;
						}
						if (!whitespace && passedWhitespace) {
							break;
						}
						m_CurrentText.pop_back();
					}
					_handled = true;
					return;
				}
				if (!m_CurrentText.empty()) {
					m_CurrentText.pop_back();
				}
				_handled = true;
				return;
			}
			if (_event.key.code == sf::Keyboard::Key::Escape) {
				setFocus(false);
				_handled = true;
				return;
			}
			if (_event.key.code == sf::Keyboard::Key::Return) {
				// TODO: Submitting?
				//m_CurrentText.clear();
				//_handled = true;
				return;
			}
		}
	}

	void TextBox::onVisualChanged(void) {
		sf::Color boundsInnerColor;
		sf::Color boundsOuterColor;
		sf::Color textColor;

		if (m_Enabled) {
			if (m_HasFocus) {
				boundsInnerColor = m_InnerActive;
				boundsOuterColor = m_OutlineActive;
				textColor = m_TextActive;
			} else {
				boundsInnerColor = m_InnerNormal;
				boundsOuterColor = m_OutlineNormal;
				textColor = m_TextNormal;
			}
		}
		else {
			boundsInnerColor = m_InnerDisabled;
			boundsOuterColor = m_OutlineDisabled;
			textColor = m_TextDisabled;
		}

		m_Bounds.setOutlineColor(boundsOuterColor);
		m_Bounds.setFillColor(boundsInnerColor);
		m_Text.setFillColor(textColor);
	}
}
