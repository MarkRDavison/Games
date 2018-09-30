#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_GAME_COMMAND_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_GAME_COMMAND_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IGameCommandService.hpp>
#include <functional>

namespace drl {
	
	class GameCommandServiceMock : public IGameCommandService {
	public:
		~GameCommandServiceMock(void) override {}

		void tick(void) override { m_Tick++; }
		long long getCurrentTick(void) const override { return m_Tick; }

		bool executeGameCommand(const GameCommand& _command) override {
			if (executeGameCommandCallback) {
				return executeGameCommandCallback(_command);
			}

			return false;
		}

		long long m_Tick;

		std::function<bool(const GameCommand&)> executeGameCommandCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_GAME_COMMAND_SERVICE_MOCK_HPP_