#include <Intrusion/Scenes/GameUiScene.hpp>
#include <Intrusion/Infrastructure/IntrusionDefinitions.hpp>

namespace itr {

	GameUiScene::GameUiScene(inf::FontManager& _fontManager, inf::TextureManager& _textureManager, inf::InputManager& _inputManager, itr::IntrusionConfigurationManager& _configurationManager, ILevelResourceService& _levelResourceService) :
		inf::Scene("itr::GameUiScene"),
		m_FontManager(_fontManager),
		m_TextureManager(_textureManager),
		m_InputManager(_inputManager),
		m_ConfigurationManager(_configurationManager),
		m_LevelResourceService(_levelResourceService) {

		updateResourceText(Definitions::LivesResourceName);
		updateResourceText(Definitions::GoldResourceName);
		updateResourceText(Definitions::KillsResourceName);
		m_LevelResourceService.resourceChanged = [this](const std::string& _resourceName) {
			updateResourceText(_resourceName);
		};
	}
	GameUiScene::~GameUiScene(void) {
		
	}

	void GameUiScene::update(float _delta) {
		
	}
	bool GameUiScene::handleEvent(const sf::Event& _event) {
		return false;
	}
	void GameUiScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		const sf::View originalView = _target.getView();
		_target.setView(_target.getDefaultView());
		const sf::Vector2f size(m_InputManager.getWindowSize());

		_states.transform.translate(size.x - 240.0f, 0.0f);

		for (const auto& text : m_ResourceTexts) {
			_target.draw(text.second, _states);
			_states.transform.translate(0.0f, 32.0f);
		}

		_target.setView(originalView);
	}

	void GameUiScene::updateResourceText(const std::string& _resourceName) {
		const int value = m_LevelResourceService.getResource(_resourceName);

		const std::string text = _resourceName + ": " + std::to_string(value);

		if (m_ResourceTexts.find(_resourceName) == m_ResourceTexts.end()) {
			sf::Text& newText = m_ResourceTexts[_resourceName];
			newText.setFillColor(sf::Color::White);
			newText.setOutlineColor(sf::Color::Black);
			newText.setOutlineThickness(2.0f);
			newText.setFont(m_FontManager.getFont("DEBUG"));
		}

		sf::Text& t = m_ResourceTexts[_resourceName];
		t.setString(text);
	}
}
