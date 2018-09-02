#ifndef INCLUDED_HURRICANE_OBJECTS_DROP_TABLE_HPP_
#define INCLUDED_HURRICANE_OBJECTS_DROP_TABLE_HPP_

#include <string>
#include <vector>

namespace hur {
	
	struct DropTable {
		std::string name;
		std::vector<std::pair<int, std::vector<std::string>>> chancesAndEntities;
	};

}

#endif // INCLUDED_HURRICANE_OBJECTS_DROP_TABLE_HPP_s