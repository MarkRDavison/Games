#include <Driller/Scenes/GameScene.hpp>
#include <Utility/Colour.hpp>
#include <Driller/DataStructures/BuildingPrototype.hpp>
#include <iostream>

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

		m_View.setCenter({});
		resizeView();
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
			if (_event.mouseButton.button == sf::Mouse::Right) {
				m_Panning = true;
				m_PanningAnchor = sf::Vector2f(m_InputManager.getMousePosition());
				return true;
			}
			if (handleMouseButton(_event.mouseButton.button, _event.mouseButton.x, _event.mouseButton.y)) {
				return true;
			}
		}
		else if (_event.type == sf::Event::MouseButtonReleased) {
			if (_event.mouseButton.button == sf::Mouse::Right) {
				m_Panning = false;
				return true;
			}
		}
		else if (_event.type == sf::Event::MouseMoved) {
			if (m_Panning) {
				const sf::Vector2f mousePosition(m_InputManager.getMousePosition());
				const sf::Vector2f offset = mousePosition - m_PanningAnchor;
				m_View.move(-1.0f * offset * m_Zoom / m_Config.getGameViewScale());
				m_PanningAnchor = mousePosition;
				return true;
			}
		}
		else if (_event.type == sf::Event::MouseWheelScrolled) {
			if (_event.mouseWheelScroll.delta > 0.0f) {
				m_Zoom /= m_ZoomSensitivity;
				zoomViewAt({ _event.mouseWheelScroll.x, _event.mouseWheelScroll.y }, 1.0f / m_ZoomSensitivity);
			}
			else if (_event.mouseWheelScroll.delta < 0.0f) {
				m_Zoom *= m_ZoomSensitivity;
				zoomViewAt({ _event.mouseWheelScroll.x, _event.mouseWheelScroll.y }, m_ZoomSensitivity);
			}
			return true;
		}
		else if (_event.type == sf::Event::KeyPressed) {
			if (_event.key.code == sf::Keyboard::F5) {
				m_Zoom = 1.0f;
				m_PanningAnchor = {};

				resizeView();
				m_View.setCenter({});
				return true;
			}
			if (_event.key.code == sf::Keyboard::Escape) {
				std::cout << "Deselected active building" << std::endl;
				m_ActiveBuilding = -1;
				return true;
			}
			if (_event.key.code == sf::Keyboard::Num1) {
				m_ActiveBuilding = 0;
				std::cout << "Selected Bunk as active building" << std::endl;
				return true;
			}
			if (_event.key.code == sf::Keyboard::Num2) {
				m_ActiveBuilding = 1;
				std::cout << "Selected Builder Hut as active building" << std::endl;
				return true;
			}
			if (_event.key.code == sf::Keyboard::Num3) {
				m_ActiveBuilding = 2;
				std::cout << "Selected Miner as active building" << std::endl;
				return true;
			}
			if (_event.key.code == sf::Keyboard::Num4) {
				m_ActiveBuilding = 3;
				std::cout << "Selected Refiner as active building" << std::endl;
				return true;
			}
			if (_event.key.code == sf::Keyboard::Num5) {
				m_ActiveBuilding = 4;
				std::cout << "Selected Researcher as active building" << std::endl;
				return true;
			}
			if (_event.key.code == sf::Keyboard::Num6) {
				m_ActiveBuilding = 5;
				std::cout << "Selected Recreation as active building" << std::endl;
				return true;
			}
			if (_event.key.code == sf::Keyboard::Num7) {
				m_ActiveBuilding = 6;
				std::cout << "Selected Dining as active building" << std::endl;
				return true;
			}
			if (_event.key.code == sf::Keyboard::Numpad7) {
				std::cout << "Attempting to research worker movement speed" << std::endl;
				if (m_GameCommandService.executeGameCommand(drl::GameCommand(drl::GameCommand::CompleteResearchEvent{ Definitions::ResearchCategory_WorkerMovementSpeed }))) {
					std::cout << "Completed research!" << std::endl;
				}
				return true;
			}
			if (_event.key.code == sf::Keyboard::Numpad8) {
				std::cout << "Attempting to research worker work speed" << std::endl;
				if (m_GameCommandService.executeGameCommand(drl::GameCommand(drl::GameCommand::CompleteResearchEvent{ Definitions::ResearchCategory_WorkerWorkSpeed }))) {
					std::cout << "Completed research!" << std::endl;
				}
				return true;
			}
		}
		else if (_event.type == sf::Event::Resized) {
			resizeView();
			return true;
		}

		return false;
	}

	void GameScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		const sf::View view = _target.getView();
		_target.setView(m_View);

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

		_target.setView(view);
	}

	bool GameScene::handleMouseButton(sf::Mouse::Button _button, const int _x, const int _y) const {
		const sf::Vector2f mousePosition = convertEventCoordinatesToLocalGameCoordinates({_x, _y});

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
			drl::GameCommand cmd = drl::GameCommand(drl::GameCommand::DigShaftEvent{level});
			cmd.commandContext = GameCommand::CommandContext::CreatingEntity;
			if (m_GameCommandService.executeGameCommand(cmd)) {
				return true;
			}
		} else {	
			if (_button == sf::Mouse::Left) {
				if (m_ActiveBuilding == -1) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
						if (col > 0) {
							for (int i = 1; i <= col; ++i) {
								m_GameCommandService.executeGameCommand(drl::GameCommand(drl::GameCommand::CreateJobEvent{ drl::Definitions::JobPrototypeName_Dig, {i, level}, {1,1}, {} }));
							}
						} else {
							for (int i = -1; i >= col; --i) {
								m_GameCommandService.executeGameCommand(drl::GameCommand(drl::GameCommand::CreateJobEvent{ drl::Definitions::JobPrototypeName_Dig, {i, level}, {1,1}, {} }));
							}
						}
					}
					else {
						if (m_GameCommandService.executeGameCommand(drl::GameCommand(drl::GameCommand::CreateJobEvent{ drl::Definitions::JobPrototypeName_Dig, {col, level}, {1,1}, {} }))) {
							return true;
						}
					}
				}
				else if (m_ActiveBuilding == 0) {
					auto e = drl::GameCommand::CreateJobEvent{ drl::Definitions::JobPrototypeName_BuildBuilding, {col, level}, {2,1}, {0.5f, 0.0f} };
					e.additionalPrototypeId = inf::djb_hash(drl::Definitions::BuildingBunkPrototypeName);
					if (m_GameCommandService.executeGameCommand(drl::GameCommand(e))) {
						return true;
					}
				}
				else if (m_ActiveBuilding == 1) {
					auto e = drl::GameCommand::CreateJobEvent{ drl::Definitions::JobPrototypeName_BuildBuilding, {col, level}, {2,1}, {0.5f, 0.0f} };
					e.additionalPrototypeId = inf::djb_hash(drl::Definitions::BuildingBuilderPrototypeName);
					if (m_GameCommandService.executeGameCommand(drl::GameCommand(e))) {
						return true;
					}
				}
				else if (m_ActiveBuilding == 2) {
					auto e = drl::GameCommand::CreateJobEvent{ drl::Definitions::JobPrototypeName_BuildBuilding, {col, level}, {3,1}, {1.0f, 0.0f} };
					e.additionalPrototypeId = inf::djb_hash(drl::Definitions::BuildingMinerPrototypeName);
					if (m_GameCommandService.executeGameCommand(drl::GameCommand(e))) {
						return true;
					}
				}
				else if (m_ActiveBuilding == 3) {
					auto e = drl::GameCommand::CreateJobEvent{ drl::Definitions::JobPrototypeName_BuildBuilding, {col, level}, {4,1}, {1.5f, 0.0f} };
					e.additionalPrototypeId = inf::djb_hash(drl::Definitions::BuildingRefinerPrototypeName);
					if (m_GameCommandService.executeGameCommand(drl::GameCommand(e))) {
						return true;
					}
				}
				else if (m_ActiveBuilding == 4) {
					auto e = drl::GameCommand::CreateJobEvent{ drl::Definitions::JobPrototypeName_BuildBuilding, {col, level}, {5,1}, {2.0f, 0.0f} };
					e.additionalPrototypeId = inf::djb_hash(drl::Definitions::BuildingResearcherPrototypeName);
					if (m_GameCommandService.executeGameCommand(drl::GameCommand(e))) {
						return true;
					}
				}
				else if (m_ActiveBuilding == 5) {
					auto e = drl::GameCommand::CreateJobEvent{ drl::Definitions::JobPrototypeName_BuildBuilding, {col, level}, {3,1}, {1.0f, 0.0f} };
					e.additionalPrototypeId = inf::djb_hash(drl::Definitions::BuildingRecreationPrototypeName);
					if (m_GameCommandService.executeGameCommand(drl::GameCommand(e))) {
						return true;
					}
				}
				else if (m_ActiveBuilding == 6) {
					auto e = drl::GameCommand::CreateJobEvent{ drl::Definitions::JobPrototypeName_BuildBuilding, {col, level}, {3,1}, {1.0f, 0.0f} };
					e.additionalPrototypeId = inf::djb_hash(drl::Definitions::BuildingDiningPrototypeName);
					if (m_GameCommandService.executeGameCommand(drl::GameCommand(e))) {
						return true;
					}
				}
			} 
		}
		
		return false;
	}

	sf::Vector2f GameScene::convertEventCoordinatesToLocalGameCoordinates(const sf::Vector2i& _coordinates) const {
		return sf::Vector2f(m_InputManager.mapPixelToCoords(_coordinates, m_View));
	}

	void GameScene::zoomViewAt(const sf::Vector2i& _pixel, float _zoom) {
		const sf::Vector2f beforeCoord{ m_InputManager.mapPixelToCoords(_pixel, m_View) };
		m_View.zoom(_zoom);
		const sf::Vector2f afterCoord{ m_InputManager.mapPixelToCoords(_pixel, m_View) };
		m_View.move(beforeCoord - afterCoord);
	}
	void GameScene::resizeView(void) {
		m_View.setSize(sf::Vector2f(m_InputManager.getWindowSize()) / m_Config.getGameViewScale());
	}
}
