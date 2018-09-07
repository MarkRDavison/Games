#ifndef INCLUDED_INTRUSION_DATA_STRUCTURES_LEVEL_CELL_HPP_
#define INCLUDED_INTRUSION_DATA_STRUCTURES_LEVEL_CELL_HPP_

namespace itr {

	struct LevelCell {
		bool empty{ true };
		bool start{ false };
		bool end{ false };
	};

}

#endif // INCLUDED_INTRUSION_DATA_STRUCTURES_LEVEL_CELL_HPP_