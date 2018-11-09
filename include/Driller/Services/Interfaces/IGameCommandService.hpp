#ifndef INCLUDED_DRILLER_SERVICE_INTERFACES_I_GAME_COMMAND_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICE_INTERFACES_I_GAME_COMMAND_SERVICE_HPP_

#include <Driller/DataStructures/GameCommand.hpp>

namespace drl {

	class IGameCommandService {
	public:
		virtual ~IGameCommandService(void) = 0;

		virtual void tick(void) = 0;
		virtual long long getCurrentTick(void) const = 0;

		virtual bool executeGameCommand(const GameCommand& _command) = 0;
	};

	inline IGameCommandService::~IGameCommandService(void) = default;
	
}

#endif // INCLUDED_DRILLER_SERVICE_INTERFACES_I_GAME_COMMAND_SERVICE_HPP_