#ifndef INCLUDED_ENTITY_COMPONENT_SYSTEM_ECS_HPP_
#define INCLUDED_ENTITY_COMPONENT_SYSTEM_ECS_HPP_

#include <cstddef>
#include <bitset>
#include <array>

namespace ecs {
	struct Component;

	constexpr std::size_t maxComponents{ 64 };
	constexpr std::size_t maxGroups{ 64 };

	using ComponentID = std::size_t;
	using Group = std::size_t; 
	
	using ComponentBitset = std::bitset<maxComponents>;
	using ComponentArray = std::array<Component*, maxComponents>;

	using GroupBitset = std::bitset<maxGroups>; 

	namespace Internal {
		inline ComponentID getUniqueComponentID() noexcept {
			static ComponentID lastID{ 0u };
			return lastID++;
		}
	}

	template <typename T>
	ComponentID getComponentTypeID() noexcept {
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
		static ComponentID typeID{ Internal::getUniqueComponentID() };
		return typeID;
	}
}

#endif // INCLUDED_ENTITY_COMPONENT_SYSTEM_ECS_HPP_