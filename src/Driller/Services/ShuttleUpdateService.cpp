#include <Driller/Services/ShuttleUpdateService.hpp>
#include <Utility/VectorMath.hpp>

namespace drl {

	ShuttleUpdateService::ShuttleUpdateService(ShuttleData& _shuttleData, IShuttleCompletionService& _shuttleCompletionService, IWorkerRecruitmentService& _workerRecruitmentService) :
		m_ShuttleData(_shuttleData),
		m_ShuttleCompletionService(_shuttleCompletionService),
		m_WorkerRecruitmentService(_workerRecruitmentService) {
		
	}

	ShuttleUpdateService::~ShuttleUpdateService(void) {
		
	}

	void ShuttleUpdateService::update(float _delta) {
		for (ShuttleInstance& shuttle : m_ShuttleData.shuttles) {
			updateShuttle(shuttle, _delta);
		}
	}

	void ShuttleUpdateService::updateShuttle(ShuttleInstance& _shuttle, float _delta) const {
		switch(_shuttle.state) {
		case ShuttleInstance::ShuttleState::Idle:
			_shuttle.state = ShuttleInstance::ShuttleState::TravellingToSurface;
			break;
		case ShuttleInstance::ShuttleState::TravellingToSurface: 
			moveShuttleTowardsLocation(_shuttle, _delta, _shuttle.landingPosition, ShuttleInstance::ShuttleState::WaitingOnSurface);
			if (_shuttle.state == ShuttleInstance::ShuttleState::WaitingOnSurface) {
				recruitWorkersForShuttle(_shuttle);
			}
			break;
		case ShuttleInstance::ShuttleState::WaitingOnSurface:
			_shuttle.loadingTime -= _delta;
			if (_shuttle.loadingTime <= 0.0f) {
				_shuttle.state = ShuttleInstance::ShuttleState::LeavingSurface;
			}
			break;
		case ShuttleInstance::ShuttleState::LeavingSurface:
			moveShuttleTowardsLocation(_shuttle, _delta, _shuttle.completePosition, ShuttleInstance::ShuttleState::Completed);
			break;
		case ShuttleInstance::ShuttleState::Completed:
			m_ShuttleCompletionService.handleShuttleCompleted(_shuttle);
			break;
		}
	}

	void ShuttleUpdateService::moveShuttleTowardsLocation(ShuttleInstance& _shuttle, float _delta, const sf::Vector2f& _target, ShuttleInstance::ShuttleState _stateIfReached) const {
		const float distanceToTarget = inf::VectorMath::distance(_shuttle.position, _target);
		const float maxMovement = Definitions::BaseShuttleSpeed * _delta; // TODO: Put this on shuttle, or use multiplier etc

		if (distanceToTarget <= maxMovement) {
			_shuttle.state = _stateIfReached;
			_shuttle.position = _target;
		}
		else {
			_shuttle.position += inf::VectorMath::normalise(_target - _shuttle.position) * maxMovement;
		}
	}

	void ShuttleUpdateService::recruitWorkersForShuttle(const ShuttleInstance& _shuttle) const {
		m_WorkerRecruitmentService.recruitWorkers(_shuttle);
	}
}
