#ifndef INCLUDED_INFRASTRUCTURE_GUI_UI_ELEMENT_HPP_
#define INCLUDED_INFRASTRUCTURE_GUI_UI_ELEMENT_HPP_

#include <SFML/Graphics.hpp>

namespace inf {
	
	class UiElement : public sf::Drawable, public sf::Transformable {
	public:
		UiElement(const std::string& _elementName);
		virtual ~UiElement(void);

		virtual void update(float _delta);
		virtual bool handleEvent(const sf::Event& _event, bool& _handled);
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override = 0;

		virtual sf::FloatRect getBounds(void) = 0;

		bool getEnabled(void) const noexcept { return m_Enabled; }
		void setEnabled(bool _enabled);
		bool getFocused(void) const noexcept { return m_HasFocus; }
		void setFocus(bool _focus);
		virtual void onEnabledChanged(bool _enabled) {}
		virtual void onHasFocusChanged(bool _hasFocus) {}
		virtual void onClickWithinBounds(sf::Mouse::Button _button, bool _pressed) {}
		virtual void onClickOutsideBounds(sf::Mouse::Button _button, bool _pressed) {}

		std::string getName(void) const noexcept { return m_Name; }

	private:
		bool handleMouseButtonPressed(const sf::Event& _event);
		bool handleMouseMoved(const sf::Event& _event);

	protected:
		std::string m_Name;
		bool m_Enabled{ true };
		bool m_HasFocus{ false };

		bool m_MouseContained{ false };
		bool m_MousePressedWithinBounds{ false };

		
	};

}


#endif // INCLUDED_INFRASTRUCTURE_GUI_BASIC_BUTINCLUDED_INFRASTRUCTURE_GUI_UI_ELEMENT_HPP_TON_HPP_

