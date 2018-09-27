#ifndef INCLUDED_POLLUTION_SERVICES_WORLD_UPDATE_SERVICE_HPP_
#define INCLUDED_POLLUTION_SERVICES_WORLD_UPDATE_SERVICE_HPP_

#include <Pollution/Services/Interfaces/IWorldUpdateService.hpp>
#include <Infrastructure/Services/Interfaces/IResourceService.hpp>

namespace pol {

	class WorldUpdateService : public IWorldUpdateService {
	public:
		WorldUpdateService(inf::IResourceService& _resourceService);
		~WorldUpdateService(void) override;

		void update(float _delta, WorldData& _worldData) override;

	private:
		inf::IResourceService& m_ResourceService;
	};

}

#endif // #define INCLUDED_POLLUTION_SERVICES_WORLD_UPDATE_SERVICE_HPP_
