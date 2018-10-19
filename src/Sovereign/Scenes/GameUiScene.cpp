#include <Sovereign/Scenes/GameUiScene.hpp>

namespace sov {

	GameUiScene::GameUiScene(ISceneChangeService& _sceneChangeService, inf::FontManager& _fontManager) :
		inf::Scene("sov::GameUiScene"),
		m_SceneChangeService(_sceneChangeService),
		m_FontManager(_fontManager) {

		for (unsigned i = 0; i < MaxDebugText; ++i) {
			auto& p = m_DebugTexts.emplace_back(std::make_pair(-1.0f, sf::Text(std::to_string(i), _fontManager.getFont(Definitions::DefaultFontName), 16)));
			p.second.setOutlineColor(sf::Color::Black);
			p.second.setOutlineThickness(2.0f);
		}
	}
	GameUiScene::~GameUiScene(void) {

	}


	void GameUiScene::update(float _delta) {
		for (auto& pair : m_DebugTexts) {
			if (pair.first > 0.0f) {
				pair.first -= _delta;
			}
		}
	}

	bool GameUiScene::handleEvent(const sf::Event& _event) {
		if (_event.type == sf::Event::KeyPressed) {
			if (_event.key.code == sf::Keyboard::F1 && _event.key.shift) {
				m_SceneChangeService.setSceneState(Definitions::GameSceneState::Title);
				return true;
			}
			if (_event.key.code == sf::Keyboard::Escape && _event.key.shift) {
				m_SceneChangeService.setSceneState(Definitions::GameSceneState::Exit);
				return true;
			}
		}
		return false;
	}

	void GameUiScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		const sf::Vector2f& Size = sf::Vector2f(_target.getSize());
		const sf::View& original = _target.getView();
		_target.setView(_target.getDefaultView());

		_states.transform.translate(0.0f, 16.0f);

		for (unsigned i = 0; i < MaxDebugText; ++i) {
			unsigned index = (i + m_CurrentIndex) % MaxDebugText;
			if (m_DebugTexts[index].first > 0.0f) {
				_target.draw(m_DebugTexts[index].second, _states);
				_states.transform.translate(0.0f, 16.0f);
			}
		}

		_target.setView(original);
	}

	void GameUiScene::log(LogLevel _level, const std::string& _log) {
		auto& pair = m_DebugTexts[m_CurrentIndex++];
		pair.first = LogTime;
		pair.second.setString(_log);
		if (m_CurrentIndex >= MaxDebugText) {
			m_CurrentIndex = 0;
		}
	}

}