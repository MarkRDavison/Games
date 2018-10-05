#ifndef INCLUDED_DRILLER_SERVICES_SHUTTLE_UPDATE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_SHUTTLE_UPDATE_SERVICE_HPP_

#include <Driller/Services/Interfaces/IShuttleUpdateService.hpp>
#include <Driller/DataStructures/ShuttleData.hpp>
#include "Interfaces/IShuttleCompletionService.hpp"
#include "Interfaces/IWorkerRecruitmentService.hpp"

namespace drl {

	class ShuttleUpdateService : public IShuttleUpdateService {
	public:
		ShuttleUpdateService(ShuttleData& _shuttleData, IShuttleCompletionService& _shuttleCompletionService, IWorkerRecruitmentService& _workerRecruitmentService);
		~ShuttleUpdateService(void) override;

		void update(float _delta) override;
		void updateShuttle(ShuttleInstance& _shuttle, float _delta) const;

		void moveShuttleTowardsLocation(ShuttleInstance& _shuttle, float _delta, const sf::Vector2f& _target, ShuttleInstance::ShuttleState _stateIfReached) const;
		void recruitWorkersForShuttle(const ShuttleInstance& _shuttle) const;

	private:
		ShuttleData& m_ShuttleData;
		IShuttleCompletionService& m_ShuttleCompletionService;
		IWorkerRecruitmentService& m_WorkerRecruitmentService;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_SHUTTLE_UPDATE_SERVICE_HPP_