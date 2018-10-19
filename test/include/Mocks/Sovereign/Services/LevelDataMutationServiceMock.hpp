#ifndef INCLUDED_MOCKS_SOVEREIGN_SERVICES_INTERFACES_I_LEVEL_DATA_MUTATION_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_SOVEREIGN_SERVICES_INTERFACES_I_LEVEL_DATA_MUTATION_SERVICE_MOCK_HPP_

#include <Sovereign/Services/Interfaces/ILevelDataMutationService.hpp>

namespace sov {

	class LevelDataMutationServiceMock : public ILevelDataMutationService {
	public:
		 ~LevelDataMutationServiceMock(void) override{}

	};

}

#endif // INCLUDED_MOCKS_SOVEREIGN_SERVICES_INTERFACES_I_LEVEL_DATA_MUTATION_SERVICE_MOCK_HPP_