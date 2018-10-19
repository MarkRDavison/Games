#ifndef INCLUDED_MOCKS_SOVEREIGN_SERVICES_PLAYER_CONTROL_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_SOVEREIGN_SERVICES_PLAYER_CONTROL_SERVICE_MOCK_HPP_

#include <Sovereign/Services/Interfaces/IPlayerControlService.hpp>
#include <Utility/TestSignal.hpp>

namespace sov {

	class PlayerControlServiceMock : public IPlayerControlService {
	public:
		~PlayerControlServiceMock(void) override {}

		bool handleEvent(const sf::Event& _event) const override {
			return handleEventCallback.invoke(_event);
		}

		bool handleKeyEvent(const sf::Event& _keyEvent) const override {
			return handleKeyEventCallback.invoke(_keyEvent);
		}

		inf::TestSignal<bool, const sf::Event&> handleEventCallback;
		inf::TestSignal<bool, const sf::Event&> handleKeyEventCallback;
	};

}

#endif // INCLUDED_MOCKS_SOVEREIGN_SERVICES_PLAYER_CONTROL_SERVICE_MOCK_HPP_