#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_IDENTIFICATION_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_IDENTIFICATION_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IIdentificationService.hpp>

namespace drl {
	
	class IdentificationServiceMock : public IIdentificationService {
	public:
		~IdentificationServiceMock(void) override {}

		EntityId generateId(void) override {
			return ++id;
		}

		EntityId id{ 0u };
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_IDENTIFICATION_SERVICE_MOCK_HPP_