#include <Driller/Scenes/GameUiScene.hpp>

namespace drl {
	GameUiScene::GameUiScene(ISceneChangeService& _sceneChangeService, IGameCommandService& _gameCommandService) :
		inf::Scene("drl::GameUiScene"),
		m_SceneChangeService(_sceneChangeService),
		m_GameCommandService(_gameCommandService) {

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

	}
}
