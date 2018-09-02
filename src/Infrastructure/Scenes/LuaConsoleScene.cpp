#include <Infrastructure/Scenes/LuaConsoleScene.hpp>
#include <Utility/Colour.hpp>

namespace inf {

	LuaConsoleScene::LuaConsoleScene(LuaConsole& _luaConsole, FontManager& _fontManager) :
		Scene("inf::LuaConsoleScene"),
		m_LuaConsole(_luaConsole),
		m_FontManager(_fontManager) {
		
	}
	LuaConsoleScene::~LuaConsoleScene(void) {
		
	}

	void LuaConsoleScene::update(float _delta) {
		
	}
	bool LuaConsoleScene::handleEvent(const sf::Event& _event) {
		if (m_LuaConsole.handleEvent(_event)) {
			return true;
		}
		if (_event.type == sf::Event::KeyPressed) {
			if (_event.key.code == sf::Keyboard::Tilde) {
				if (!m_LuaConsole.isOpen()) {
					m_LuaConsole.setOpen(true);
					return true;
				}
			}
		}
		return false;
	}
	void LuaConsoleScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		const float ConsoleHeight = 32.0f;
		const float Margin = 2.0f;
		const sf::View& originalView = _target.getView();
		_target.setView(_target.getDefaultView());
		sf::RenderStates states = sf::RenderStates::Default;
		states.transform.translate(Margin, _target.getSize().y - 32.0f);
		if (m_LuaConsole.isOpen()) {
			sf::RectangleShape r = sf::RectangleShape({ static_cast<float>(_target.getSize().x) - Margin * 2.0f, ConsoleHeight - Margin});
			r.setOutlineColor(inf::Colour::DarkGrey);
			r.setFillColor(sf::Color::White);
			r.setOutlineThickness(Margin);
			_target.draw(r, states);

			sf::Text text = sf::Text(m_LuaConsole.getCurrentText(), m_FontManager.getFont("DEBUG"));
			text.setFillColor(sf::Color::Black);
			states.transform.translate(0.0f, -6.0f);
			_target.draw(text, states);
		}
		_target.setView(originalView);
	}

}
