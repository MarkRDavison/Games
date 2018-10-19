#ifndef INCLUDED_DRILLER_SERVICES_SHUTTLE_CARGO_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_SHUTTLE_CARGO_SERVICE_HPP_

#include <Driller/Services/Interfaces/IShuttleCargoService.hpp>
#include <Infrastructure/Services/Interfaces/IResourceService.hpp>

namespace drl {
	
	class ShuttleCargoService : public IShuttleCargoService {
	public:
		ShuttleCargoService(inf::IResourceService& _resourceService);
		~ShuttleCargoService(void) override;

		void loadShuttleWithCargo(ShuttleInstance& _shuttle) override;

	private:
		inf::IResourceService& m_ResourceService;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_SHUTTLE_CARGO_SERVICE_HPP_