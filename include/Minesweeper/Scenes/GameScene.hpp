#ifndef INCLUDED_MINESWEEPER_SCENES_GAME_SCENE_HPP_
#define INCLUDED_MINESWEEPER_SCENES_GAME_SCENE_HPP_

#include <Minesweeper/Services/Interfaces/ISceneChangeService.hpp>
#include <Minesweeper/GameObjects/GameBoard.hpp>
#include <Minesweeper/Infrastructure/ConfigurationManager.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Minesweeper/Services/Interfaces/IBoardStatusService.hpp>

namespace swp {
	
	class GameScene : public inf::Scene {
	public:
		GameScene(inf::TextureManager& _textureManager, inf::InputManager& _inputManager, ConfigurationManager& _config, ISceneChangeService& _sceneChangeService, IBoardStatusService& _boardStatusService, IBoardInteractionService& _boardInteractionService);
		~GameScene(void) override;

		void setGameBoard(GameBoard *_gameBoard);

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

	private:
		void updateFaceTextureRect(const sf::Vector2i& _coordinates);

	private:
		inf::TextureManager& m_TextureManager;
		inf::InputManager& m_InputManager;
		ConfigurationManager& m_Config;
		ISceneChangeService& m_SceneChangeService;
		IBoardStatusService& m_BoardStatusService;
		IBoardInteractionService& m_BoardInteractionService;

		GameBoard *m_GameBoard{ nullptr };
		bool m_RenderHoveredCellGraphic{ false };
		bool m_GameOver{ false };
		sf::RectangleShape m_HoveredCellGraphic;

		sf::Sprite m_FaceSprite;
	};

}

#endif // INCLUDED_MINESWEEPER_SCENES_GAME_SCENE_HPP_