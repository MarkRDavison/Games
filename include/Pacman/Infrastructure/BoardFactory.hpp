#ifndef INCLUDED_PACMAN_INFRSTRUCTURE_BOARD_FACTORY_HPP_
#define INCLUDED_PACMAN_INFRSTRUCTURE_BOARD_FACTORY_HPP_

namespace pacman {
	class Board;
	class BoardFactory {
	public:
		static Board * createStandardBoard(void);
	};

}

#endif // INCLUDED_PACMAN_INFRSTRUCTURE_BOARD_FACTORY_HPP_