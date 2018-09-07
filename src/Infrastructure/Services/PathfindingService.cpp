#include <Infrastructure/Services/PathfindingService.hpp>
#include <algorithm>

namespace inf {
	

	Path PathfindingService::findPath(int _xStart, int _yStart, int _xEnd, int _yEnd, const IPathSurface& _pathSurface) const {
		Path path{};

		std::vector<std::vector<InternalPathNode>> currentGraph(_pathSurface.getHeight(), std::vector<InternalPathNode>(_pathSurface.getWidth()));

		for (unsigned y = 0; y < _pathSurface.getHeight(); ++y) {
			for (unsigned x = 0; x < _pathSurface.getWidth(); ++x) {
				InternalPathNode& n = currentGraph[y][x];
				n.x = static_cast<int>(x);
				n.y = static_cast<int>(y);
				n.canTraverse = _pathSurface.canTraverse({ static_cast<unsigned>(x) , static_cast<unsigned>(y) });
				if (y == _yStart && x == _xStart) {
					n.start = true;
					n.cost = 0;
					n.open = true;
				}
				if (y == _yEnd && x == _xEnd) {
					n.end = true;
					if (!n.canTraverse) {
						path.isValid = false;
						return path;
					}
				}
			}
		}

		std::vector<InternalPathNode *> open{ &currentGraph[_yStart][_xStart] };
		std::vector<InternalPathNode *> closed{};		

		while (open.size() > 0) {
			const auto lowest = std::min_element(open.begin(), open.end(), [](InternalPathNode *_first, InternalPathNode *_second) {return _first->cost < _second->cost; });
			InternalPathNode *current = *lowest;
			current->open = false;
			current->closed = true;
			closed.push_back(current);
			open.erase(lowest);
			
			const auto& neighbourCoords = _pathSurface.getValidNeighbours({ static_cast<unsigned int>(current->x), static_cast<unsigned int>(current->y) });
			std::vector<InternalPathNode *> neighbours(neighbourCoords.size());
			std::transform(neighbourCoords.begin(), neighbourCoords.end(), neighbours.begin(), [&](const sf::Vector2u& _coord) { return &currentGraph[_coord.y][_coord.x]; });

			for (InternalPathNode *neighbour : neighbours) {
				if (neighbour->closed || !neighbour->canTraverse) {
					continue;
				}

				const int gScore = calculateG(_xStart, _yStart, neighbour->x, neighbour->y);
				const int hScore = calculateH(neighbour->x, neighbour->y, _xEnd, _yEnd);

				if (!neighbour->open) {
					open.push_back(neighbour);
					neighbour->parent = current;
					neighbour->g = gScore;
					neighbour->h = hScore;
					neighbour->cost = gScore + hScore;
					neighbour->open = true;
				}
				else if (neighbour->g > gScore) {
					neighbour->parent = current;
					neighbour->g = gScore;
					neighbour->h = hScore;
					neighbour->cost = gScore + hScore;
				}
			}
		}

		InternalPathNode *currentNode = &currentGraph[_yEnd][_xEnd];
		path.isValid = currentNode != nullptr && currentNode->end;
		while (currentNode != nullptr) {
			PathNode node{};
			node.x = currentNode->x;
			node.y = currentNode->y;

			if (currentNode->start) {
				node.nodeType = PathNode::NodeType::Start;
			} else if (currentNode->end) {
				node.nodeType = PathNode::NodeType::End;
			} else {
				node.nodeType = PathNode::NodeType::Standard;
			}

			path.nodes.push_back(node);

			currentNode = currentNode->parent;
		}
		
		std::reverse(path.nodes.begin(), path.nodes.end());

		return path;
	}
	int PathfindingService::calculateH(int _xCurrent, int _yCurrent, int _xEnd, int _yEnd) const {
		return abs(_xCurrent - _xEnd) + abs(_yCurrent - _yEnd);
	}
	int PathfindingService::calculateG(int _xStart, int _yStart, int _xCurrent, int _yCurrent) const {
		return abs(_xStart - _xCurrent) + abs(_yStart - _yCurrent);		
	}
}