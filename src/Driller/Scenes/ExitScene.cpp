#include <Driller/Scenes/ExitScene.hpp>

namespace drl {
	ExitScene::ExitScene(ISceneChangeService& _sceneChangeService) :
		inf::Scene("drl::ExitScene"),
		m_SceneChangeService(_sceneChangeService) {

	}
	ExitScene::~ExitScene(void) {

	}

	void ExitScene::update(float _delta) {
		m_ExitTimeRemaining -= _delta;
		if (m_ExitTimeRemaining <= 0.0f) {
			m_SceneChangeService.closeApplication();
		}
	}

	bool ExitScene::handleEvent(const sf::Event & _event) {
		return false;
	}

	void ExitScene::draw(sf::RenderTarget & _target, sf::RenderStates _states, float _alpha) const {
		const sf::Vector2f& Size = sf::Vector2f(_target.getSize());
		const sf::View& original = _target.getView();
		_target.setView(_target.getDefaultView());

		_states.transform.translate(Size / 2.0f);

		{
			sf::RenderStates s(_states);
			s.transform.translate(100.0f, 0.0f);
			const float Radius = 48.0f;
			sf::CircleShape c(Radius);
			c.setOrigin(Radius, Radius);
			c.setFillColor(sf::Color::Blue);
			c.setFillColor(sf::Color(0, 0, 255, static_cast<sf::Uint8>(m_ExitTimeRemaining > 0.0f ? m_ExitTimeRemaining / m_ExitTime * 255.0f : 0.0f)));
			_target.draw(c, s);
		}

		{
			sf::RenderStates s(_states);
			s.transform.translate(-100.0f, 0.0f);
			const float Radius = 48.0f;
			sf::CircleShape c(Radius);
			c.setOrigin(Radius, Radius);
			c.setFillColor(sf::Color::Blue);
			c.setFillColor(sf::Color(0, 0, 255, static_cast<sf::Uint8>(m_ExitTimeRemaining > 0.0f ? m_ExitTimeRemaining / m_ExitTime * 255.0f : 0.0f)));
			_target.draw(c, s);
		}

		{
			const float Radius = 64.0f;
			sf::CircleShape c(Radius);
			c.setOrigin(Radius, Radius);
			c.setFillColor(sf::Color::Yellow);
			c.setFillColor(sf::Color(255, 0, 0, static_cast<sf::Uint8>(m_ExitTimeRemaining > 0.0f ? m_ExitTimeRemaining / m_ExitTime * 255.0f : 0.0f)));
			_target.draw(c, _states);
		}

		_target.setView(original);
	}
}