#ifndef INCLUDED_KINGDOM_EXCEPTIONS_SURFACE_NOT_FOUND_EXCEPTION_HPP_
#define INCLUDED_KINGDOM_EXCEPTIONS_SURFACE_NOT_FOUND_EXCEPTION_HPP_
#include <stdexcept>

namespace kdm {
	
	class SurfaceNotFoundException : public std::runtime_error {
	public:
		SurfaceNotFoundException(void) :
			SurfaceNotFoundException("'Nameless'") {
			
		}
		SurfaceNotFoundException(const std::string& _message)
			: std::runtime_error(std::string(_message + " surface was not found")) {
			
		}
	};

}

#endif // INCLUDED_KINGDOM_EXCEPTIONS_SURFACE_NOT_FOUND_EXCEPTION_HPP_