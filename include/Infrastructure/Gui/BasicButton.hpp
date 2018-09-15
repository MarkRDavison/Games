#ifndef INCLUDED_INFRASTRUCTURE_GUI_BASIC_BUTTON_HPP_
#define INCLUDED_INFRASTRUCTURE_GUI_BASIC_BUTTON_HPP_

#include <Infrastructure/Gui/UiElement.hpp>

#include <functional>

namespace inf {
	
	class BasicButton : public UiElement {
	public:
		enum class ButtonColor {
			OutlineHovered,
			OutlineNormal,
			OutlinePressed,
			OutlineDisabled,
			InnerHovered,
			InnerNormal,
			InnerPressed,
			InnerDisabled
		};

		explicit BasicButton(const std::string& _name);
		~BasicButton(void) override;

		bool handleEvent(const sf::Event& _event, bool& _handled) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

		sf::FloatRect getBounds(void) override;

		void setSize(const sf::Vector2f& _size);
		void setCallback(std::function<void(bool)> _callback);
		void onClickWithinBounds(sf::Mouse::Button _button, bool _pressed) override;

		void onEnabledChanged(bool _enabled) override;

		void setColour(const sf::Color& _color, ButtonColor _colorType);

	protected:
		void onVisualChanged(void);

	private:
		sf::RectangleShape m_Bounds;
		std::function<void(bool)> m_Callback;

		sf::Color m_OutlineHovered		{sf::Color::Magenta};
		sf::Color m_OutlineNormal		{ sf::Color::Cyan };
		sf::Color m_OutlinePressed		{ sf::Color::Red };
		sf::Color m_OutlineDisabled		{ sf::Color::Blue };
		sf::Color m_InnerHovered		{ sf::Color::White };
		sf::Color m_InnerNormal			{ sf::Color::Yellow };
		sf::Color m_InnerPressed		{ sf::Color::Green };
		sf::Color m_InnerDisabled		{ sf::Color(64, 64, 64) };
	};

}


#endif // INCLUDED_INFRASTRUCTURE_GUI_BASIC_BUTTON_HPP_
