#ifndef INCLUDED_POLLUTION_DATA_STRUCTURES_ANIMATION_DATA_HPP_
#define INCLUDED_POLLUTION_DATA_STRUCTURES_ANIMATION_DATA_HPP_

#include <vector>

namespace pol {
	
	struct Animation {
		struct Frame {
			float duration{ 0.0f };
			sf::IntRect bounds;
		};

		std::vector<Frame> frames;
	};

}

#endif // INCLUDED_POLLUTION_DATA_STRUCTURES_ANIMATION_DATA_HPP_