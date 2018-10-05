#include <Driller/Scenes/GameUiScene.hpp>

namespace drl {
	GameUiScene::GameUiScene(ISceneChangeService& _sceneChangeService, inf::FontManager& _fontManager, inf::ResourceService& _resourceService, IGameCommandService& _gameCommandService) :
		inf::Scene("drl::GameUiScene"),
		m_SceneChangeService(_sceneChangeService),
		m_FontManager(_fontManager),
		m_ResourceService(_resourceService),
		m_GameCommandService(_gameCommandService) {

		updateResourceText(Definitions::MoneyResourceName);
		updateResourceText(Definitions::OreResourceName);
		updateResourceText(Definitions::CurrentBuilderResourceName);

		m_ResourceService.resourceChanged.registerCallback([this](const std::string& _resourceName) {
			updateResourceText(_resourceName);
		});
	}
	GameUiScene::~GameUiScene(void) {

	}

	void GameUiScene::update(float _delta) {

	}

	bool GameUiScene::handleEvent(const sf::Event & _event) {
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

	void GameUiScene::draw(sf::RenderTarget & _target, sf::RenderStates _states, float _alpha) const {
		const sf::View OriginalView = _target.getView();
		_target.setView(_target.getDefaultView());

		for (const auto& text : m_ResourceTexts) {
			_states.transform.translate(0.0f, 16.0f);
			_target.draw(text.second, _states);
		}


		_target.setView(OriginalView);
	}

	void GameUiScene::updateResourceText(const std::string& _resourceName) {
		const int value = m_ResourceService.getResource(_resourceName);
		const int max = m_ResourceService.getResourceMax(_resourceName);

		const std::string text = _resourceName + ": " + std::to_string(value) + (max != inf::IResourceService::DefaultResourceMaximum ? (" / " + std::to_string(max)) : "");
		// TODO: Include max in here if set
		if (m_ResourceTexts.find(_resourceName) == m_ResourceTexts.end()) {
			sf::Text& newText = m_ResourceTexts[_resourceName];
			newText.setCharacterSize(16);
			newText.setFillColor(sf::Color::White);
			newText.setOutlineColor(sf::Color::Black);
			newText.setOutlineThickness(2.0f);
			newText.setFont(m_FontManager.getFont("DEBUG"));
		}

		sf::Text& t = m_ResourceTexts[_resourceName];
		t.setString(text);
	}
}
