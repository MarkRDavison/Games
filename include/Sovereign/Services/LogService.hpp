#ifndef INCLUDED_SOVEREIGN_SERVICES_LOG_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_LOG_SERVICE_HPP_

#include <Sovereign/Services/Interfaces/ILogService.hpp>
#include <Utility/Signal.hpp>

namespace sov {
	
	class LogService : public ILogService {
	public:
		~LogService(void) override;

		void log(LogLevel _level, const std::string& _message) override;

		inf::Signal<LogLevel, const std::string&> onLog;
	};

}

#endif // INCLUDED_SOVEREIGN_SERVICES_LOG_SERVICE_HPP_