#include <Minesweeper/Scenes/TitleScene.hpp>
#include <Utility/TextHelpers.hpp>

namespace swp {

	TitleScene::TitleScene(inf::TextureManager& _textureManager, inf::FontManager& _fontManager, inf::InputManager& _inputManager, ISceneChangeService& _sceneChangeService) :
		inf::Scene("swp::TitleScene"),
		m_TextureManager(_textureManager),
		m_FontManager(_fontManager),
		m_InputManager(_inputManager),
		m_SceneChangeService(_sceneChangeService),
		m_TitleText("Minesweeper", _fontManager.getFont("DEBUG"), 128),
		m_PlayText("Play", _fontManager.getFont("DEBUG")),
		m_QuitText("Quit", _fontManager.getFont("DEBUG")) {

		inf::TextHelpers::centerText(m_TitleText);
		inf::TextHelpers::centerText(m_PlayText);
		inf::TextHelpers::centerText(m_QuitText);
	}
	TitleScene::~TitleScene(void) {
		
	}

	void TitleScene::update(float _delta) {
		sf::Vector2f mousePosition = sf::Vector2f(m_InputManager.getMousePosition());
		const sf::Vector2f size(m_InputManager.getWindowSize());

		mousePosition -= sf::Vector2f(size.x / 2.0f, size.y * 3.0f / 5.0f);

		m_PlayTextContainsMouse = m_PlayText.getGlobalBounds().contains(mousePosition);

		mousePosition -= sf::Vector2f(0.0f, size.y * 1.0f / 5.0f);
		m_QuitTextContainsMouse = m_QuitText.getGlobalBounds().contains(mousePosition);

		m_PlayText.setFillColor(!m_PlayTextContainsMouse ? sf::Color::White : sf::Color::Yellow);
		m_QuitText.setFillColor(!m_QuitTextContainsMouse ? sf::Color::White : sf::Color::Yellow);
	}
	bool TitleScene::handleEvent(const sf::Event& _event) {
		if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left) {
			if (handleMousePressed()) {
				return true;
			}
		}

		if (_event.type == sf::Event::KeyPressed) {
			if (_event.key.code == sf::Keyboard::Escape && _event.key.shift) {
				m_SceneChangeService.changeToGameScene();
				return true;
			}
		}
		return false;
	}
	void TitleScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		const sf::View originalView = _target.getView();
		_target.setView(_target.getDefaultView());
		const sf::Vector2f size(m_InputManager.getWindowSize());

		_states.transform.translate(size.x / 2.0f, size.y / 5.0f);

		_target.draw(m_TitleText, _states);

		_states.transform.translate(0.0f, size.y / 5.0f);
		_states.transform.translate(0.0f, size.y / 5.0f);
		_target.draw(m_PlayText, _states);
		_states.transform.translate(0.0f, size.y / 5.0f);
		_target.draw(m_QuitText, _states);

		_target.setView(originalView);
	}

	bool TitleScene::handleMousePressed(void) {
		
		if (m_PlayTextContainsMouse) {
			m_SceneChangeService.changeToGameScene();
			return true;
		}

		if (m_QuitTextContainsMouse) {
			m_SceneChangeService.changeToExitScene();
			return true;
		}

		return false;

	}

}
