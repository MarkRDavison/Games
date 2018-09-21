#ifndef INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_PROJECTILE_HPP_
#define INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_PROJECTILE_HPP_

namespace itr {
	
	struct ParsedProjectile {
		std::string prototypeName;
		float speed{ 1.0f };
		float baseDamage{ 1.0f };
	};

}

#endif // INCLUDED_INTRUSION_DATA_STRUCTURES_PARSED_PROJECTILE_HPP_