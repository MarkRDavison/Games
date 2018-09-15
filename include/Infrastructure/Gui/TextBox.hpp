#ifndef INCLUDED_INFRASTRUCTURE_GUI_TEXT_BOX_HPP_
#define INCLUDED_INFRASTRUCTURE_GUI_TEXT_BOX_HPP_

#include <Infrastructure/Gui/UiElement.hpp>

namespace inf {

	class TextBox : public UiElement {
	public:
		enum class TextBoxColor {
			OutlineNormal,
			OutlineDisabled,
			OutlineActive,
			InnerNormal,
			InnerDisabled,
			InnerActive,
			TextNormal,
			TextDisabled,
			TextActive
		};

		explicit TextBox(const std::string& _name);
		~TextBox(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event, bool& _handled) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

		sf::FloatRect getBounds(void) override;
		void onEnabledChanged(bool _enabled) override;
		void onHasFocusChanged(bool _hasFocus) override;
		void onClickWithinBounds(sf::Mouse::Button _button, bool _pressed) override;
		void onClickOutsideBounds(sf::Mouse::Button _button, bool _pressed) override;

		void setSize(const sf::Vector2f& _size);

		void setColour(const sf::Color& _color, TextBoxColor _colorType);
		void setFont(const sf::Font& _font);
		void setText(const std::string& _text);

		void handleTextEnteredEvent(const sf::Event& _event, bool& _handled);
		void handleKeyPressedEvent(const sf::Event& _event, bool& _handled);

	protected:
		void onVisualChanged(void);

	protected:
		sf::RectangleShape m_Bounds;
		sf::Text m_Text;
		std::string m_CurrentText;

		sf::Color m_OutlineNormal		{ sf::Color::Red };
		sf::Color m_OutlineDisabled		{ sf::Color::Blue };
		sf::Color m_OutlineActive		{ sf::Color::Green };
		sf::Color m_InnerNormal			{ sf::Color::Magenta };
		sf::Color m_InnerDisabled		{ sf::Color::Cyan };
		sf::Color m_InnerActive			{ sf::Color::Yellow };
		sf::Color m_TextNormal			{ sf::Color::White };
		sf::Color m_TextDisabled		{ sf::Color(64, 64, 64) };
		sf::Color m_TextActive			{ sf::Color::Black };
	};
	
}

#endif // INCLUDED_INFRASTRUCTURE_GUI_TEXT_BOX_HPP_