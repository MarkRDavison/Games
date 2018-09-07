#ifndef INCLUDED_INFRASTRUCTURE_GUI_UI_ELEMENT_HPP_
#define INCLUDED_INFRASTRUCTURE_GUI_UI_ELEMENT_HPP_

#include <SFML/Graphics.hpp>

namespace inf {
	
	class UiElement : public sf::Drawable, public sf::Transformable {
	public:
		UiElement(const std::string& _elementName);
		virtual ~UiElement(void);

		virtual void update(float _delta);
		virtual bool handleEvent(const sf::Event& _event);
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override = 0;

		virtual sf::FloatRect getBounds(void) = 0;

		bool getEnabled(void) const noexcept { return m_Enabled; }
		void setEnabled(bool _enabled);
		virtual void onEnabledChanged(bool _enabled) {}
		virtual void onClick(sf::Mouse::Button _button, bool _pressed) const {}

		std::string getName(void) const noexcept { return m_Name; }

	private:
		bool handleMouseButtonPressed(const sf::Event& _event);
		bool handleMouseMoved(const sf::Event& _event);

	protected:
		std::string m_Name;
		bool m_Enabled{ true };

		bool m_MouseContained{ false };
		bool m_MousePressed{ false };

		
	};

}


#endif // INCLUDED_INFRASTRUCTURE_GUI_BASIC_BUTINCLUDED_INFRASTRUCTURE_GUI_UI_ELEMENT_HPP_TON_HPP_

