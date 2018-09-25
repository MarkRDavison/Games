#include <Pollution/Scenes/GameScene.hpp>
#include <Utility/VectorMath.hpp>

namespace pol {
	
	GameScene::GameScene(inf::InputManager& _inputManager, ConfigurationManager& _configurationManager) :
		inf::Scene("pol::GameScene"),
		m_InputManager(_inputManager),
		m_Config(_configurationManager) {
		
	}
	GameScene::~GameScene(void) {

	}

	void GameScene::update(float _delta) {
		
	}
	bool GameScene::handleEvent(const sf::Event& _event) {
		return false;
	}
	void GameScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		const sf::Vector2f& Size = sf::Vector2f(_target.getSize());
		const float Scale = m_Config.getGameViewScale();
		const float SideAngleSize = 360.0f / m_World.Sides;

		_states.transform.translate(Size / (2.0f * Scale));
		_states.transform.rotate(0.0f);

		{
			const float Radius = 1.0f;
			sf::CircleShape c(Radius);
			c.setOrigin(Radius, Radius);
			c.setFillColor(sf::Color::Magenta);
			_target.draw(c, _states);
		}

		{
			const sf::Vector2f& mousePosition = sf::Vector2f(m_InputManager.getMousePositionRelativeToCenter()) / Scale;

			const sf::Vector2f dir = inf::VectorMath::normalise(mousePosition);
			const float length = inf::VectorMath::length(mousePosition);
			float angle = inf::VectorMath::toAngle(dir, inf::VectorMath::AngleType::Degrees);
			if (angle < 0.0f) {
				angle += 360.0f;
			}

			int sideIndex = static_cast<int>((angle + SideAngleSize / 2.0f) / SideAngleSize);
			if (sideIndex >= m_World.Sides) {
				sideIndex -= m_World.Sides;
			}

			const float Radius = 0.05f;
			sf::CircleShape c(Radius);

			if (1.0f - m_World.SnapMargin <= length && length <= 1.0f + m_World.SnapMargin) {
				c.setPosition(inf::VectorMath::toDirection(sideIndex * SideAngleSize, inf::VectorMath::AngleType::Degrees));
				c.setFillColor(sf::Color::Green);
			} else {
				c.setPosition(mousePosition);
				c.setFillColor(sf::Color::Red);
			}
			c.setOrigin(Radius, Radius);
			_target.draw(c, _states);
		}

	}

	void GameScene::initialise(const WorldDataInitialisationPackage& _worldInitialisationPackage) {
		m_World.Sides = _worldInitialisationPackage.Sides;
		m_World.SnapMargin = _worldInitialisationPackage.SnapMargin;
	}

}
