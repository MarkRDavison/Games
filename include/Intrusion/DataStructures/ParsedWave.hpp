#ifndef INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_WAVE_HPP_
#define INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_WAVE_HPP_

#include <string>

namespace itr {
	
	struct WaveInstance {
		float time{ 1.0f };				// Time after the previous wave has finished spawning until this one starts (-1.0f means spawn immediatly and go onto the next as well (multiple waves at once))
		float interval{ 0.0f };			// Interval between entities on the same wave
		float intervalTimer{ 0.0f };
		unsigned amount{ 1 };			// Number of entities in the wave
		unsigned waveIndex{ 0 };		// The index of this wave within the level
		std::string entityPrototype;	// The entity prototype to spawn
	};

}

#endif // INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_WAVE_HPP_