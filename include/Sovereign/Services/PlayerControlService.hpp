#ifndef INCLUDED_SOVEREIGN_SERVICES_PLAYER_CONTROL_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_PLAYER_CONTROL_SERVICE_HPP_

#include <Sovereign/Services/Interfaces/IPlayerControlService.hpp>
#include <Sovereign/DataStructures/EntityData.hpp>
#include <Sovereign/DataStructures/ControlBindings.hpp>

namespace sov {

	class PlayerControlService : public IPlayerControlService {
	public:
		PlayerControlService(EntityData& _entityData, ControlBindings& _controlBindings);
		~PlayerControlService(void) override;

		bool handleEvent(const sf::Event& _event) const override;
		bool handleKeyEvent(const sf::Event& _keyEvent) const override;

	private:
		EntityData& m_EntityData;
		ControlBindings& m_ControlBindings;
	};

}

#endif // INCLUDED_SOVEREIGN_SERVICES_PLAYER_CONTROL_SERVICE_HPP_