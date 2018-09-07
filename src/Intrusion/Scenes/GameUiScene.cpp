#include <Intrusion/Scenes/GameUiScene.hpp>

namespace itr {

	GameUiScene::GameUiScene(inf::FontManager& _fontManager, inf::TextureManager& _textureManager, inf::InputManager& _inputManager, itr::IntrusionConfigurationManager& _configurationManager) :
		inf::Scene("itr::GameUiScene"),
		m_FontManager(_fontManager),
		m_TextureManager(_textureManager),
		m_InputManager(_inputManager),
		m_ConfigurationManager(_configurationManager) {
		
	}
	GameUiScene::~GameUiScene(void) {
		
	}

	void GameUiScene::update(float _delta) {
		
	}
	bool GameUiScene::handleEvent(const sf::Event& _event) {
		return false;
	}
	void GameUiScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		
	}

}