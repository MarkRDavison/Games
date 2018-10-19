#include <Sovereign/Services/LogService.hpp>

namespace sov {

	LogService::~LogService(void) {
		
	}

	void LogService::log(LogLevel _level, const std::string& _message) {
		onLog.invoke(_level, _message);
	}

}