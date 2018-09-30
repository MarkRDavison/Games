#ifndef INCLUDED_UTILITY_HASH_HPP_
#define INCLUDED_UTILITY_HASH_HPP_

#include <cstdlib>

namespace inf {
	static std::size_t djb_hash(const char* _str) {
		std::size_t hash = 5381;
		while (*_str) {
			hash = 33 * hash ^ static_cast<unsigned char>(*_str++);
		}
		return hash;
	}
}

#endif // INCLUDED_UTILITY_HASH_HPP_