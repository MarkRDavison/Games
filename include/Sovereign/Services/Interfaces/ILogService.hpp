#ifndef INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_LOG_SERVICE_HPP_
#define INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_LOG_SERVICE_HPP_

#include <Sovereign/Enumerations/LogLevel.hpp>
#include <string>

namespace sov {
	
	class ILogService {
	protected:
		virtual ~ILogService(void) = 0 {}
			   
	public:
		virtual void log(LogLevel _level, const std::string& _message) = 0;

	};

}

#endif // INCLUDED_SOVEREIGN_SERVICES_INTERFACES_I_LOG_SERVICE_HPP_