#include <Sovereign/Scenes/GameScene.hpp>
#include <Utility/Colour.hpp>
#include <Utility/VectorMath.hpp>
#include <algorithm>
#include <iostream>
#include <cmath>

namespace sov {

	void appendCell(sf::VertexArray& _vertexArray, const sf::Vector2u& _coordinates, const sf::Vector2u& _textureCell, const sf::Color& _color) {
		const float TextureSize = 32.0f;
		_vertexArray.append(sf::Vertex(
			sf::Vector2f(static_cast<float>(_coordinates.x + 0) * Definitions::TileSize, static_cast<float>(_coordinates.y + 0) * Definitions::TileSize),
			_color,
			sf::Vector2f(static_cast<float>(_textureCell.x + 0) * TextureSize, static_cast<float>(_textureCell.y + 0) * TextureSize)));
		_vertexArray.append(sf::Vertex(
			sf::Vector2f(static_cast<float>(_coordinates.x + 1) * Definitions::TileSize, static_cast<float>(_coordinates.y + 0) * Definitions::TileSize),
			_color,
			sf::Vector2f(static_cast<float>(_textureCell.x + 1) * TextureSize, static_cast<float>(_textureCell.y + 0) * TextureSize)));
		_vertexArray.append(sf::Vertex(
			sf::Vector2f(static_cast<float>(_coordinates.x + 1) * Definitions::TileSize, static_cast<float>(_coordinates.y + 1) * Definitions::TileSize),
			_color,
			sf::Vector2f(static_cast<float>(_textureCell.x + 1) * TextureSize, static_cast<float>(_textureCell.y + 1) * TextureSize)));

		_vertexArray.append(sf::Vertex(
			sf::Vector2f(static_cast<float>(_coordinates.x + 0) * Definitions::TileSize, static_cast<float>(_coordinates.y + 0) * Definitions::TileSize),
			_color,
			sf::Vector2f(static_cast<float>(_textureCell.x + 0) * TextureSize, static_cast<float>(_textureCell.y + 0) * TextureSize)));
		_vertexArray.append(sf::Vertex(
			sf::Vector2f(static_cast<float>(_coordinates.x + 1) * Definitions::TileSize, static_cast<float>(_coordinates.y + 1) * Definitions::TileSize),
			_color,
			sf::Vector2f(static_cast<float>(_textureCell.x + 1) * TextureSize, static_cast<float>(_textureCell.y + 1) * TextureSize)));
		_vertexArray.append(sf::Vertex(
			sf::Vector2f(static_cast<float>(_coordinates.x + 0) * Definitions::TileSize, static_cast<float>(_coordinates.y + 1) * Definitions::TileSize),
			_color,
			sf::Vector2f(static_cast<float>(_textureCell.x + 0) * TextureSize, static_cast<float>(_textureCell.y + 1) * TextureSize)));
	}

	GameScene::GameScene(inf::IConfigurationManager& _config, inf::InputManager& _inputManager, inf::TextureManager& _textureManager, ILogService& _logService, ISceneChangeService& _sceneChangeService, Game& _game) :
		inf::Scene("sov::GameScene"),
		m_Config(_config),
		m_InputManager(_inputManager),
		m_TextureManager(_textureManager),
		m_LogService(_logService),
		m_SceneChangeService(_sceneChangeService),
		m_Game(_game) {

		m_View.setCenter({});
		resizeView(); 
		
		cells = sf::VertexArray(sf::Triangles);

		regenerateTerrain();
	}
	GameScene::~GameScene(void) {

	}


	void GameScene::update(float _delta) {


		m_Game.update(_delta);
	}
	
	float getAngleRelativeOrigin(const sf::Vector2f& _coordinates) {
		const sf::Vector2f dir = inf::VectorMath::normalise(_coordinates);
		float angle = inf::VectorMath::toAngle(dir, inf::VectorMath::AngleType::Degrees);
		if (angle < 0.0f) {
			angle += 360.0f;
		}
		else if (angle >= 360.0f) {
			angle -= 360.0f;
		}

		return angle;
	}

	void GameScene::zoomViewAt(const sf::Vector2i& _pixel, float _zoom) {
		const sf::Vector2f beforeCoord{ m_InputManager.mapPixelToCoords(_pixel, m_View) };
		m_View.zoom(_zoom);
		const sf::Vector2f afterCoord{ m_InputManager.mapPixelToCoords(_pixel, m_View) };
		m_View.move(beforeCoord - afterCoord);
	}

	bool GameScene::handlePickup(const MoveableEntity& _me) const {
		const MoveableEntity& player = m_Game.m_EntityDataQueryService.getEntityById(m_Game.m_EntityData.playerId);

		if (inf::VectorMath::distance(player.position, _me.position) > player.pickupRange) {
			m_LogService.log(LogLevel::Information, "Entity " + std::to_string(_me.id) + " is out of range to pickup");
			return false;
		}

		m_Game.m_EntityDataMutationService.removeEntity(_me.id);

		m_LogService.log(LogLevel::Information, "Picking up entity " + std::to_string(_me.id));

		return true;
	}

	bool GameScene::handleMineStart(const MoveableEntity& _me) const {
		const MoveableEntity& player = m_Game.m_EntityDataQueryService.getEntityById(m_Game.m_EntityData.playerId);

		if (inf::VectorMath::distance(player.position, _me.position) > player.mineRange) {
			m_LogService.log(LogLevel::Information, "Entity " + std::to_string(_me.id) + " is out of range to mine");
			return false;
		}

		m_Game.m_EntityDataMutationService.mineEntity(_me.id, 0.0f);

		m_LogService.log(LogLevel::Information, "Mining entity " + std::to_string(_me.id));

		return true;
	}

	bool GameScene::handleEvent(const sf::Event& _event) {
		if (_event.type == sf::Event::MouseButtonPressed) {
			if (_event.mouseButton.button == m_Game.m_ControlBindings.panButton) {
				m_Panning = true;
				m_PanningAnchor = sf::Vector2f(m_InputManager.getMousePosition());
				return true;
			}
			if (_event.mouseButton.button == m_Game.m_ControlBindings.actionButtom) {
				const sf::Vector2f pos = convertEventCoordinatesToLocalGameCoordinates({ _event.mouseButton.x, _event.mouseButton.y });
				if (m_Game.m_EntityDataQueryService.doesMoveableEntityExistAtCoordinates(pos.x, pos.y)) {
					const MoveableEntity& me = m_Game.m_EntityDataQueryService.getMoveableEntityAtCoordinates(pos.x, pos.y);

					if (me.isPickup) {
						return handlePickup(me);
					}

					if (me.isMineable) {
						return handleMineStart(me);
					}

					m_LogService.log(LogLevel::Information, "Cannot interact with entity " + std::to_string(me.id));
				}

				return false;
			}
		}
		else if (_event.type == sf::Event::MouseButtonReleased) {
			if (_event.mouseButton.button == m_Game.m_ControlBindings.panButton) {
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
				m_LogService.log(LogLevel::Information, "Camera reset");
				return true;
			}
		}
		else if (_event.type == sf::Event::Resized) {
			resizeView();
			return true;
		}
		if (m_Game.handleEvent(_event)) {
			return true;
		}
		return false;
	}

	void GameScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		const sf::View view = _target.getView();
		_target.setView(m_View);
		_states.texture = &m_TextureManager.getTexture(Definitions::TerrainTextureName);
		

		_target.draw(cells, _states);

		for (const auto& me : m_Game.m_EntityData.moveableEntities) {
			sf::RenderStates entityStates(_states);
			entityStates.transform.translate(me.position);
			sf::RectangleShape player = sf::RectangleShape(me.size);
			player.setOrigin(me.size / 2.0f);
			player.setFillColor(me.isPlayer ? sf::Color::Yellow : (me.isPickup ? m_PickupColor : (me.isMineable ? m_MineColor : sf::Color::Black)));
			_target.draw(player, entityStates);

			if (me.isPlayer) {
				{
					sf::CircleShape c(me.pickupRange);
					c.setOrigin(me.pickupRange, me.pickupRange);
					c.setFillColor(sf::Color::Transparent);
					c.setOutlineColor(m_PickupColor);
					c.setOutlineThickness(0.05f);

					_target.draw(c, entityStates);
				}
				{
					sf::CircleShape c(me.mineRange);
					c.setOrigin(me.mineRange, me.mineRange);
					c.setFillColor(sf::Color::Transparent);
					c.setOutlineColor(m_MineColor);
					c.setOutlineThickness(0.05f);

					_target.draw(c, entityStates);
				}
			}
		}

		_target.setView(view);
	}

	sf::Vector2f GameScene::convertEventCoordinatesToLocalGameCoordinates(const sf::Vector2i& _coordinates) const {
		return sf::Vector2f(m_InputManager.mapPixelToCoords(_coordinates, m_View));
	}

	void GameScene::resizeView(void) {
		m_View.setSize(sf::Vector2f(m_InputManager.getWindowSize()) / m_Config.getGameViewScale());
	}

	void GameScene::regenerateTerrain(void) {
		cells.clear();
		for (const LevelChunk& chunk : m_Game.m_LevelData.levelChunks) {
			for (unsigned y = 0; y < Definitions::ChunkSize; ++y) {
				for (unsigned x = 0; x < Definitions::ChunkSize; ++x) {
					appendCell(cells, { chunk.x * Definitions::ChunkSize + x, chunk.y * Definitions::ChunkSize + y }, { 0, 0 }, chunk.cells[y * Definitions::ChunkSize + x].empty ? sf::Color::Green : sf::Color::Red);
				}
			}
		}
	}

}
