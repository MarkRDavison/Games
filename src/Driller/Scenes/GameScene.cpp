#include <Driller/Scenes/GameScene.hpp>
#include <Utility/Colour.hpp>
#include <Driller/DataStructures/BuildingPrototype.hpp>

namespace drl {
	GameScene::GameScene(inf::IConfigurationManager& _config, inf::InputManager& _inputManager, ISceneChangeService& _sceneChangeService, IGameCommandService& _gameCommandService, Game& _game, TerrainView& _terrainView, BuildingView& _buildingView, JobView& _jobView, WorkerView& _workerView, ShuttleView& _shuttleView) :
		inf::Scene("drl::GameScene"),
		m_Config(_config),
		m_InputManager(_inputManager),
		m_SceneChangeService(_sceneChangeService),
		m_GameCommandService(_gameCommandService),
		m_Game(_game),
		m_TerrainView(_terrainView),
		m_BuildingView(_buildingView),
		m_JobView(_jobView),
		m_WorkerView(_workerView),
		m_ShuttleView(_shuttleView) {

		const auto& Size = m_InputManager.getWindowSize();
		m_CameraOffset = sf::Vector2f(static_cast<float>(Size.x / 2) / m_Config.getGameViewScale(), static_cast<float>(Size.x / 8) / m_Config.getGameViewScale());
	}
	GameScene::~GameScene(void) {

	}

	void GameScene::update(float _delta) {
		m_Game.update(_delta);

		m_TerrainView.update(_delta);
		m_BuildingView.update(_delta);
		m_JobView.update(_delta);
		m_WorkerView.update(_delta);
		m_ShuttleView.update(_delta);
	}

	bool GameScene::handleEvent(const sf::Event & _event) {
		if (_event.type == sf::Event::MouseButtonPressed) {
			if (handleMouseButton(_event.mouseButton.button, _event.mouseButton.x, _event.mouseButton.y)) {
				return true;
			}
		}

		if (_event.type == sf::Event::KeyPressed) {
			if (_event.key.code == sf::Keyboard::F5) {
				m_GameCommandService.executeGameCommand(GameCommand{ GameCommand::ResetJobAllocationsEvent{} });
				return true;
			}
		}

		return false;
	}

	void GameScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		_states.transform.translate(m_CameraOffset);

		{
			sf::RectangleShape sky({ 50.0f, 50.0f });
			sky.setOrigin(sky.getSize().x / 2.0f, sky.getSize().y);
			sky.setFillColor(sf::Color::Cyan);
			_target.draw(sky, _states);
		}
		{
			sf::RectangleShape ground({ 50.0f, 50.0f });
			ground.setOrigin(ground.getSize().x / 2.0f, 0.0f);
			ground.setFillColor(inf::Colour::Brown);
			_target.draw(ground, _states);
		}

		m_TerrainView.draw(_target, _states, _alpha);
		m_BuildingView.draw(_target, _states, _alpha);
		m_JobView.draw(_target, _states, _alpha);
		m_ShuttleView.draw(_target, _states, _alpha);
		m_WorkerView.draw(_target, _states, _alpha);
	}

	bool GameScene::handleMouseButton(sf::Mouse::Button _button, const int _x, const int _y) {
		const sf::Vector2f mousePosition = sf::Vector2f(static_cast<float>(_x), static_cast<float>(_y)) / m_Config.getGameViewScale() - m_CameraOffset;

		if (mousePosition.y < 0.0f) {
			return false;
		}

		const int level = static_cast<int>(std::floorf(mousePosition.y));
		int col;

		if (std::abs(mousePosition.x) <= Definitions::TileSize / 2.0f) {
			col = 0;
		} else {
			col = static_cast<int>(std::floorf(std::abs(mousePosition.x) + Definitions::TileSize / 2.0f)) * (mousePosition.x > 0.0f ? +1 : -1);
		}

		if (col == 0) {
			// Handle maybe building shaft
			if (m_GameCommandService.executeGameCommand(drl::GameCommand(drl::GameCommand::DigShaftEvent{ level }))) {
				return true;
			}
		} else {	
			if (_button == sf::Mouse::Left) {
				if (m_GameCommandService.executeGameCommand(drl::GameCommand(drl::GameCommand::CreateJobEvent{ drl::Definitions::JobPrototypeName_Dig, {col, level}, {1,1}, {} }))) {
					return true;
				}
			} else if (_button == sf::Mouse::Right) {
				auto e = drl::GameCommand::CreateJobEvent{ drl::Definitions::JobPrototypeName_BuildBuilding, {col, level}, {2,1}, {0.5f, 0.0f} };
				e.additionalPrototypeId = inf::djb_hash(drl::Definitions::BuildingBunkPrototypeName);
				if (m_GameCommandService.executeGameCommand(drl::GameCommand(e))) {
					return true;
				}
			} else if (_button == sf::Mouse::Middle) {
				auto e = drl::GameCommand::CreateJobEvent{ drl::Definitions::JobPrototypeName_BuildBuilding, {col, level}, {2,1}, {0.5f, 0.0f} };
				e.additionalPrototypeId = inf::djb_hash(drl::Definitions::BuildingBuilderPrototypeName);
				if (m_GameCommandService.executeGameCommand(drl::GameCommand(e))) {
					return true;
				}
			} else if (_button == sf::Mouse::XButton1) {
				// Side Back Button
			} else if (_button == sf::Mouse::XButton1) {
				// Side Forward Button
			}
		}
		
		return false;
	}
}
