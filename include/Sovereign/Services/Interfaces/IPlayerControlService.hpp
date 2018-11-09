#ifndef INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_PLAYER_CONTROL_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_PLAYER_CONTROL_SERVICE_HPP_

#include <SFML/Window/Event.hpp>

namespace sov {

	class IPlayerControlService {
	protected:
		virtual ~IPlayerControlService(void) = 0;

	public:
		virtual bool handleEvent(const sf::Event& _event) const = 0;
		virtual bool handleKeyEvent(const sf::Event& _keyEvent) const = 0;
	};

	inline IPlayerControlService::~IPlayerControlService(void) = default;
	
}

#endif // INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_PLAYER_CONTROL_SERVICE_HPP_