#ifndef INCLUDED_DRILLER_SERVICES_SHUTTLE_CREATION_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_SHUTTLE_CREATION_SERVICE_HPP_

#include <Driller/Services/Interfaces/IShuttleCreationService.hpp>
#include <Driller/Services/Interfaces/IPrototypeService.hpp>
#include <Driller/DataStructures/ShuttleData.hpp>

namespace drl {
	
	class ShuttleCreationService : public IShuttleCreationService {
	public:
		ShuttleCreationService(ShuttleData& _shuttleData, IShuttlePrototypeService& _shuttlePrototypeService);
		~ShuttleCreationService(void) override;

		bool canCreateShuttle(const GameCommand::CreateShuttleEvent& _event) override;
		void createShuttle(const GameCommand::CreateShuttleEvent& _event) override;

		bool doesShuttlePrototypeExistAsInstance(const ShuttlePrototypeId& _prototypeId) const;

	private:
		ShuttleData& m_ShuttleData;
		IShuttlePrototypeService& m_ShuttlePrototypeService;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_SHUTTLE_CREATION_SERVICE_HPP_