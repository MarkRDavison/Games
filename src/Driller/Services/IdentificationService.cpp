#include <Driller/Services/IdentificationService.hpp>

namespace drl {

	IdentificationService::~IdentificationService(void) {
		
	}

	EntityId IdentificationService::generateId(void) {
		return m_EntityId++;
	}

}
