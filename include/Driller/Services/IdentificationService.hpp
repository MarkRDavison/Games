#ifndef INCLUDED_DRILLER_SERVICES_IDENTIFICATION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_IDENTIFICATION_SERVICE_HPP_

#include <Driller/Services/Interfaces/IIdentificationService.hpp>

namespace drl {

	class IdentificationService : public IIdentificationService {
	public:
		~IdentificationService(void) override;

		EntityId generateId(void) override;

	private:
		EntityId m_EntityId{ 1u };
	};

}

#endif // INCLUDED_DRILLER_SERVICES_IDENTIFICATION_SERVICE_HPP_