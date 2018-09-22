#include <Minesweeper/Scenes/ExitScene.hpp>
#include <Utility/TextHelpers.hpp>
#include <sstream>
#include <iomanip>

namespace swp {

	ExitScene::ExitScene(inf::FontManager& _fontManager, inf::InputManager& _inputManager, ISceneChangeService& _sceneChangeService) :
		inf::Scene("swp::ExitScene"),
		m_FontManager(_fontManager),	
		m_InputManager(_inputManager),
		m_SceneChangeService(_sceneChangeService),
		m_CountdownText("2.00...", m_FontManager.getFont("DEBUG"), 256) {

		inf::TextHelpers::centerText(m_CountdownText);

	}
	ExitScene::~ExitScene(void) {

	}

	void ExitScene::update(float _delta) {
		m_Countdown -= _delta;

		if (m_Countdown <= 0.0f) {
			if (m_SceneChangeService.closeApplication) {
				m_SceneChangeService.closeApplication();
			}
		}
		else {
			std::stringstream strstr;
			strstr << std::fixed << std::setprecision(2) << m_Countdown;

			m_CountdownText.setString(strstr.str() + "...");
		}
	}
	bool ExitScene::handleEvent(const sf::Event& _event) {
		return false;
	}
	void ExitScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		const sf::View originalView = _target.getView();
		_target.setView(_target.getDefaultView());
		const sf::Vector2f size(m_InputManager.getWindowSize());
		
		_states.transform.translate(size.x / 2.0f, size.y / 2.0f);

		_target.draw(m_CountdownText, _states);

		_target.setView(originalView);
	}

}
