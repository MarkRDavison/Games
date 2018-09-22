#include <Minesweeper/Scenes/GameScene.hpp>
#include <Minesweeper/Infrastructure/Definitions.hpp>

namespace swp {

	GameScene::GameScene(inf::TextureManager& _textureManager, inf::InputManager& _inputManager, ConfigurationManager& _config, ISceneChangeService& _sceneChangeService, IBoardStatusService& _boardStatusService, IBoardInteractionService& _boardInteractionService) :		inf::Scene("swp::GameScene"),
		m_TextureManager(_textureManager),
		m_InputManager(_inputManager),
		m_Config(_config),
		m_SceneChangeService(_sceneChangeService),
		m_BoardStatusService(_boardStatusService),
		m_BoardInteractionService(_boardInteractionService),
		m_FaceSprite(_textureManager.getTexture(Definitions::FaceSpriteSheetTextureName)) {

		updateFaceTextureRect(Definitions::HappyFaceTileCoords);
		m_FaceSprite.setScale(1.0f / _config.getGameViewScale(), 1.0f / _config.getGameViewScale());

		m_BoardStatusService.winSignal.registerCallback([&](void) {
			m_BoardInteractionService.revealWin(*m_GameBoard);
			m_BoardInteractionService.setEnabled(false);
		});
		m_BoardStatusService.loseSignal.registerCallback([&](const sf::Vector2i& _coordinates) {
			m_GameBoard->m_InteractionState.gameLost = true;
			m_BoardInteractionService.revealAll(*m_GameBoard, _coordinates);
			m_BoardInteractionService.setEnabled(false);
		});
		
	}
	GameScene::~GameScene(void) {
		if (m_GameBoard != nullptr) {
			delete m_GameBoard;
		}
	}

	void GameScene::setGameBoard(GameBoard* _gameBoard) {
		m_GameBoard = _gameBoard;

		m_HoveredCellGraphic.setSize(sf::Vector2f(Definitions::CellSize, Definitions::CellSize));
		m_HoveredCellGraphic.setFillColor(sf::Color::Transparent);
		m_HoveredCellGraphic.setOutlineColor(sf::Color::Yellow);
		m_HoveredCellGraphic.setOutlineThickness(Definitions::CellSize / 20.0f);

		m_FaceSprite.move(_gameBoard->m_Size.x * Definitions::CellSize, 0.0f);

		m_BoardStatusService.winSignal.registerCallback([&](void) {
			updateFaceTextureRect(Definitions::WinFaceTileCoords);
			m_GameOver = true;
		});
		m_BoardStatusService.loseSignal.registerCallback([&](const sf::Vector2i&) {
			updateFaceTextureRect(Definitions::LoseFaceTileCoords);
			m_GameOver = true;
		});
		m_BoardStatusService.onPress = [&](void) {
			updateFaceTextureRect(Definitions::WinceFaceTileCoords);
		};
		m_BoardStatusService.onRelease = [&](void) {
			updateFaceTextureRect(Definitions::HappyFaceTileCoords);
		};
	}

	void GameScene::update(float _delta) {
		if (m_GameBoard != nullptr) {
			m_GameBoard->update(_delta);

			m_RenderHoveredCellGraphic = true;

			const sf::Vector2f mousePosition(sf::Vector2f(m_InputManager.getMousePosition()) / (m_Config.getGameViewScale() * Definitions::CellSize));
			const sf::Vector2i cellCoordinates(mousePosition);

			m_HoveredCellGraphic.setPosition(sf::Vector2f(cellCoordinates));

			if (mousePosition.x < 0.0f || mousePosition.y < 0.0f) {
				m_RenderHoveredCellGraphic = false;
			}

			if (cellCoordinates.x + 1 > static_cast<int>(m_GameBoard->m_Size.x) ||
				cellCoordinates.y + 1 > static_cast<int>(m_GameBoard->m_Size.y)) {
				m_RenderHoveredCellGraphic = false;
			}
		}
	}
	bool GameScene::handleEvent(const sf::Event& _event) {
		if (_event.type == sf::Event::KeyPressed) {
			if (_event.key.code == sf::Keyboard::F5) {
				m_SceneChangeService.changeToGameScene();
				return true;
			}
			if (_event.key.code == sf::Keyboard::Escape && _event.key.shift) {
				m_SceneChangeService.changeToExitScene();
				return true;
			}
		}

		if (m_GameBoard != nullptr) {
			if (m_GameBoard->handleEvent(_event)) {
				return true;
			}
		}
		return false;
	}
	void GameScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		if (m_GameBoard != nullptr) {
			m_GameBoard->draw(_target, _states, _alpha);
			if (m_RenderHoveredCellGraphic && !m_GameOver) {
				_target.draw(m_HoveredCellGraphic, _states);
			}
			_target.draw(m_FaceSprite, _states);
		}
	}

	void GameScene::updateFaceTextureRect(const sf::Vector2i& _coordinates) {
		m_FaceSprite.setTextureRect(sf::IntRect(_coordinates * 32, { 32, 32 }));
	}

}
