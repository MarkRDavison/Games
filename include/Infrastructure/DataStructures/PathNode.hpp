#ifndef INCLUDED_INFRASTRUCTURE_DATA_STRUCTURES_PATH_NODE_HPP_
#define INCLUDED_INFRASTRUCTURE_DATA_STRUCTURES_PATH_NODE_HPP_

namespace inf {
	
	struct PathNode {
		int x{0};
		int y{0};
		//float offsetX{ 0.0f };
		//float offsetY{ 0.0f };
		enum class NodeType {
			Start,
			End,
			Standard
		} nodeType {NodeType::Standard};
	};

}

#endif // INCLUDED_INFRASTRUCTURE_DATA_STRUCTURES_PATH_NODE_HPP_