#include <Intrusion/Scenes/StartScene.hpp>
#include <Utility/Colour.hpp>
#include <Intrusion/Infrastructure/IntrusionDefinitions.hpp>
#include <iostream>

namespace itr {

	StartScene::StartScene(inf::FontManager& _fontManager, inf::TextureManager& _textureManager, itr::IntrusionConfigurationManager& _configurationManager, inf::InputManager& _inputManager) :
		inf::Scene("itr::StartScene"),
		m_FontManager(_fontManager),
		m_TextureManager(_textureManager),
		m_ConfigurationManager(_configurationManager),
		m_InputManager(_inputManager),
		m_IconSprite(m_TextureManager.getTexture(Definitions::SpearIconTextureName)),
		m_TestButton1("m_TestButton1"),
		m_TestButton2("m_TestButton2") {

		const sf::Vector2f size{ 64.0f, 64.0f };

		m_IconSprite.setOrigin(size / 2.0f);

		m_TestButton1.setSize(size);
		m_TestButton1.setOrigin(size / 2.0f);
		m_TestButton2.setSize(size);
		m_TestButton2.setOrigin(size / 2.0f);

		m_TestButton1.setCallback([this](bool _pressed) {
			if (_pressed) {
				m_TestButton2.setEnabled(!m_TestButton2.getEnabled());
			}
		});
		m_TestButton2.setCallback([](bool _pressed) {
			std::cout << "Button 2 pressed: " << _pressed << std::endl;
		});

		updateUiPositions();
	}
	StartScene::~StartScene(void) {
		
	}

	void StartScene::update(float _delta) {

	}

	bool StartScene::handleEvent(const sf::Event& _event) {
		bool handled = false;
		if (m_TestButton1.handleEvent(_event)) {
			handled = true;
		}
		if (m_TestButton2.handleEvent(_event)) {
			handled = true;
		}
		return handled;
	}
	void StartScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		const sf::View originalView = _target.getView();
		_target.setView(_target.getDefaultView());

		_target.clear(inf::Colour::NatureGreen);

		_target.draw(m_IconSprite, _states);

		_target.draw(m_TestButton1, _states);
		_target.draw(m_TestButton2, _states);

		_target.setView(originalView);
	}

	void StartScene::updateUiPositions(void) {
		const sf::Vector2f size(m_InputManager.getWindowSize());

		m_IconSprite.move(size.x / 2.0f, 40.0f);

		m_TestButton1.move(size.x / 2.0f, size.y / 2.0f);
		m_TestButton2.move(size.x / 2.0f + 96.0f, size.y / 2.0f);
	}
}
