#ifndef INCLUDED_DRILLER_SERVICES_SHUTTLE_UPDATE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_SHUTTLE_UPDATE_SERVICE_HPP_

#include <Driller/Services/Interfaces/IShuttleUpdateService.hpp>
#include <Driller/Services/Interfaces/IShuttleCargoService.hpp>
#include <Driller/Services/Interfaces/IShuttleCompletionService.hpp>
#include <Driller/Services/Interfaces/IWorkerRecruitmentService.hpp>
#include <Driller/DataStructures/ShuttleData.hpp>

namespace drl {

	class ShuttleUpdateService : public IShuttleUpdateService {
	public:
		ShuttleUpdateService(ShuttleData& _shuttleData, IShuttleCompletionService& _shuttleCompletionService, IShuttleCargoService& _shuttleCargoService, IWorkerRecruitmentService& _workerRecruitmentService);
		~ShuttleUpdateService(void) override;

		void update(float _delta) override;
		void updateShuttle(ShuttleInstance& _shuttle, float _delta) const;

		void moveShuttleTowardsLocation(ShuttleInstance& _shuttle, float _delta, const sf::Vector2f& _target, ShuttleInstance::ShuttleState _stateIfReached) const;
		void recruitWorkersForShuttle(const ShuttleInstance& _shuttle) const;
		void placeCargoOnBoard(ShuttleInstance& _shuttle);

	private:
		ShuttleData& m_ShuttleData;
		IShuttleCompletionService& m_ShuttleCompletionService;
		IWorkerRecruitmentService& m_WorkerRecruitmentService;
		IShuttleCargoService& m_ShuttleCargoService;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_SHUTTLE_UPDATE_SERVICE_HPP_