#include <Driller/Scenes/TitleScene.hpp>
#include <Utility/TextHelpers.hpp>

namespace drl {
	TitleScene::TitleScene(inf::FontManager& _fontManager, inf::TextureManager& _textureManager, ISceneChangeService& _sceneChangeService) :
		inf::Scene("drl::TitleScene"),
		m_FontManager(_fontManager),
		m_TextureManager(_textureManager),
		m_SceneChangeService(_sceneChangeService),
		m_TitleText("Driller", m_FontManager.getFont("DEBUG"), 144),
		m_PressAnyKeyToStartText("Press any key to start...", m_FontManager.getFont("DEBUG")) {

		inf::TextHelpers::centerText(m_TitleText);
		inf::TextHelpers::centerText(m_PressAnyKeyToStartText);

		m_PressAnyKeyToStartText.setFillColor(sf::Color::Yellow);
	}
	TitleScene::~TitleScene(void) {

	}

	void TitleScene::update(float _delta) {

	}

	bool TitleScene::handleEvent(const sf::Event & _event) {
		if (_event.type == sf::Event::KeyPressed || _event.type == sf::Event::MouseButtonPressed) {
			m_SceneChangeService.setSceneState(Definitions::GameSceneState::Gameplay);
			return true;
		}
		return false;
	}

	void TitleScene::draw(sf::RenderTarget & _target, sf::RenderStates _states, float _alpha) const {
		const sf::Vector2f& Size = sf::Vector2f(_target.getSize());
		const sf::View& original = _target.getView();
		_target.setView(_target.getDefaultView());

		_states.transform.translate(Size.x / 2.0f, static_cast<float>(m_TitleText.getCharacterSize()));

		_target.draw(m_TitleText, _states);

		_states.transform.translate(0.0f, Size.y / 2.0f);

		_target.draw(m_PressAnyKeyToStartText, _states);

		_target.setView(original);
	}
}
