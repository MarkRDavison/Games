#ifndef INCLUDED_MINESWEEPER_GAME_OBJECTS_GAME_BOARD_HPP_
#define INCLUDED_MINESWEEPER_GAME_OBJECTS_GAME_BOARD_HPP_

#include <SFML/Graphics.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Minesweeper/DataStructures/Cell.hpp>
#include <Minesweeper/Services/Interfaces/IBoardInteractionService.hpp>
#include <Minesweeper/DataStructures/BoardInteractionState.hpp>

namespace swp {
	class IBoardInitializationService;

	class GameBoard {
	public:
		GameBoard(inf::TextureManager& _textureManager, IBoardInteractionService& _boardInteractionService);
		~GameBoard(void);

		void initialize(const sf::Vector2u& _size, unsigned _mines);
		void initializeGraphics(void);

		void update(float _delta);
		bool handleEvent(const sf::Event& _event);
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const;

		Cell& getCell(const sf::Vector2i& _coordinates);

		void updateTextureForCell(const sf::Vector2u& _coordinates);
		void updateTextureForCell(const sf::Vector2i& _coordinates);

		unsigned m_TotalMines{0};
		sf::Vector2u m_Size;
		std::vector<Cell> m_Cells;
		BoardInteractionState m_InteractionState;

	private:

	private:
		inf::TextureManager& m_TextureManager;
		IBoardInteractionService& m_BoardInteractionService;
		sf::VertexArray m_Graphics;
	};
}

#endif // INCLUDED_MINESWEEPER_GAME_OBJECTS_GAME_BOARD_HPP_