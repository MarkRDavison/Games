#include <Driller/Services/WorkerUpdateService.hpp>
#include <Utility/VectorMath.hpp>
#include <Utility/Hash.hpp>
#include <iostream>
#include <cassert>
#include <string>

namespace drl {

	WorkerUpdateService::WorkerUpdateService(WorkerData& _workerData, BuildingData&  _buildingData, JobData& _jobData, IJobCompletionService& _jobCompletionService, INeedProviderLocationService& _needProviderLocationService) :
		m_WorkerData(_workerData),
		m_BuildingData(_buildingData),
		m_JobData(_jobData),
		m_JobCompletionService(_jobCompletionService),
		m_NeedProviderLocationService(_needProviderLocationService) {
		
	}
	WorkerUpdateService::~WorkerUpdateService(void) {
		
	}

	void WorkerUpdateService::update(float _delta) {
		for (WorkerInstance& worker : m_WorkerData.workers) {
			updateWorker(worker, _delta);
		}
	}

	void WorkerUpdateService::updateWorker(WorkerInstance& _worker, float _delta) {
		switch (_worker.state) {
		case WorkerInstance::WorkerState::Idle:
			updateIdleWorker(_worker, _delta);
			return;
		case WorkerInstance::WorkerState::MovingToJob: 
			updateMovingToJobWorker(_worker, _delta);
			return;
		case WorkerInstance::WorkerState::MovingToNeed:
			updateMovingToNeedWorker(_worker, _delta);
			return;
		case WorkerInstance::WorkerState::WorkingJob:
			updateWorkingJobWorker(_worker, _delta);
			return;
		case WorkerInstance::WorkerState::RestoringNeed:
			updateRestoringNeedWorker(_worker, _delta);
			return;
		default:
			break;
		}
	}

	void WorkerUpdateService::updateIdleWorker(WorkerInstance& _worker, float _delta) {
		if (_worker.hasAllocatedJob && _worker.allocatedJobId != 0u) {
			_worker.state = WorkerInstance::WorkerState::MovingToJob;
			return;
		}
	}

	void WorkerUpdateService::populatePath(WorkerInstance& _worker, const sf::Vector2i& _targetCoordinates, WorkerInstance::WorkerState _stateWhenTargetReached) {
		const sf::Vector2i current = sf::Vector2i(_worker.position);

		if (current == _targetCoordinates) {
			_worker.state = _stateWhenTargetReached;
			return;
		}

		_worker.path.path.isValid = true;
		_worker.path.path.nodes.emplace_back(inf::PathNode{ current.x, current.y, inf::PathNode::NodeType::Start });

		if (current.y != _targetCoordinates.y) {
			_worker.path.path.nodes.emplace_back(inf::PathNode{ 0, current.y, inf::PathNode::NodeType::Standard });
			_worker.path.path.nodes.emplace_back(inf::PathNode{ 0, _targetCoordinates.y, inf::PathNode::NodeType::Standard });
		}

		_worker.path.path.nodes.emplace_back(inf::PathNode{ _targetCoordinates.x, _targetCoordinates.y, inf::PathNode::NodeType::End });
	}

	void WorkerUpdateService::followPath(WorkerInstance& _worker, float _delta, WorkerInstance::WorkerState _stateWhenTargetReached) const {
		const inf::PathNode node = _worker.path.path.nodes.front();
		const sf::Vector2f currentNodeTarget(sf::Vector2i(node.x, node.y));

		const float distanceToTarget = inf::VectorMath::distance(_worker.position, currentNodeTarget);
		const float maxMovement = m_WorkerData.workerMovementSpeed * _delta;

		if (distanceToTarget <= maxMovement) {
			_worker.path.path.nodes.erase(_worker.path.path.nodes.begin());
			_worker.position = currentNodeTarget;

			if (node.nodeType == inf::PathNode::NodeType::End) {
				_worker.path.path.isValid = false;
				_worker.state = _stateWhenTargetReached;
				return;
			}

			const float remainingDelta = _delta - _delta * (distanceToTarget / maxMovement);

			followPath(_worker, remainingDelta, _stateWhenTargetReached);
		}
		else {
			_worker.position += inf::VectorMath::normalise(currentNodeTarget - _worker.position) * maxMovement;
		}
	}

	void WorkerUpdateService::sendTowardsNeedProvider(WorkerInstance& _worker, EntityId _needProviderId) {
		if (_needProviderId == 0u) {
			return;
		}

		BuildingInstance& _buildingInstance = retrieveBuilding(_needProviderId);
		for (BuildingProvidedNeed& bpn : _buildingInstance.providedNeeds) {
			if (bpn.allocatedWorkerId == 0u) {
				bpn.allocatedWorkerId = _worker.Id;
				const sf::Vector2i target = _buildingInstance.coordinates + sf::Vector2i(bpn.offset);
				_worker.state = WorkerInstance::WorkerState::MovingToNeed;
				populatePath(_worker, target, WorkerInstance::WorkerState::RestoringNeed);
				return;
			}
		}
	}

	void WorkerUpdateService::updateMovingToNeedWorker(WorkerInstance& _worker, float _delta) {
		if (!_worker.path.path.nodes.empty()) {
			followPath(_worker, _delta, WorkerInstance::WorkerState::RestoringNeed);
		}
	}

	void WorkerUpdateService::updateMovingToJobWorker(WorkerInstance& _worker, float _delta) {
		if (!_worker.hasAllocatedJob || _worker.allocatedJobId == 0u) {
			_worker.state = WorkerInstance::WorkerState::Idle;
			_worker.hasAllocatedJob = false;
			_worker.allocatedJobId = 0u;
			_worker.path.path.isValid = false;
			_worker.path.path.nodes.clear();
			return;
		}

		if (!_worker.path.path.isValid) {
			JobInstance& job = retrieveJob(_worker.allocatedJobId);
			const sf::Vector2i target = job.coordinates;
			populatePath(_worker, target, WorkerInstance::WorkerState::WorkingJob);
		} else if (!_worker.path.path.nodes.empty()) {
			followPath(_worker, _delta, WorkerInstance::WorkerState::WorkingJob);
		}
	}

	void WorkerUpdateService::updateWorkingJobWorker(WorkerInstance& _worker, float _delta) {
		assert(_worker.allocatedJobId != 0);
		JobInstance& job = retrieveJob(_worker.allocatedJobId);

		job.workPerformed += _delta * m_WorkerData.workerWorkSpeed;
		updateWorkerNeeds(_worker, _delta);
		if (job.workPerformed >= job.workRequired) {
			if (!job.repeats) {
				m_JobCompletionService.handleJobCompleted(job);
				resetWorkerAfterCompletingJob(_worker, job);
			}

			if (m_JobCompletionService.isJobCompleteDelegateRegistered(job.prototypeId)) {
				JobCompleteDelegate& jobComplete = m_JobCompletionService.getJobCompleteDelegate(job.prototypeId);
				jobComplete(job);
			}

			if (job.repeats) {
				job.workPerformed -= job.workRequired;
			}
		}
	}

	void WorkerUpdateService::updateWorkerNeeds(WorkerInstance& _worker, float _delta) {
		_worker.needs.fun -= _delta;
		_worker.needs.sleep -= _delta;
		_worker.needs.nutrition -= _delta;

		if (_worker.needs.fun <= _worker.needs.funMinimum) {
			if (m_NeedProviderLocationService.isNeedProviderAvailable(inf::djb_hash(Definitions::NeedCategory_Fun))) {
				_worker.restoringNeedProviderId = m_NeedProviderLocationService.getNeedProvider(inf::djb_hash(Definitions::NeedCategory_Fun), _worker.position);
				sendTowardsNeedProvider(_worker, _worker.restoringNeedProviderId);
			}
		}
		if (_worker.needs.sleep <= _worker.needs.sleepMinimum) {
			if (m_NeedProviderLocationService.isNeedProviderAvailable(inf::djb_hash(Definitions::NeedCategory_Sleep))) {
				_worker.restoringNeedProviderId = m_NeedProviderLocationService.getNeedProvider(inf::djb_hash(Definitions::NeedCategory_Sleep), _worker.position);
				sendTowardsNeedProvider(_worker, _worker.restoringNeedProviderId);
			}
		}
		if (_worker.needs.nutrition <= _worker.needs.nutritionMinimum) {
			if (m_NeedProviderLocationService.isNeedProviderAvailable(inf::djb_hash(Definitions::NeedCategory_Nutrition))) {
				_worker.restoringNeedProviderId = m_NeedProviderLocationService.getNeedProvider(inf::djb_hash(Definitions::NeedCategory_Nutrition), _worker.position);
				sendTowardsNeedProvider(_worker, _worker.restoringNeedProviderId);
			}
		}
	}

	void WorkerUpdateService::updateRestoringNeedWorker(WorkerInstance& _worker, float _delta) {
		assert(_worker.restoringNeedProviderId != 0u);

		BuildingInstance& needProvider = retrieveBuilding(_worker.restoringNeedProviderId);

		if (needProvider.providedNeedId == inf::djb_hash(Definitions::NeedCategory_Fun)) {
			_worker.needs.fun += _delta * needProvider.providedNeedRate;
			if (_worker.needs.fun >= Definitions::BaseNeedMax_Fun) {
				_worker.needs.fun = Definitions::BaseNeedMax_Fun;
				_worker.state = WorkerInstance::WorkerState::Idle;
				_worker.restoringNeedProviderId = 0u;
				for (BuildingProvidedNeed& providedNeed : needProvider.providedNeeds) {
					if (providedNeed.allocatedWorkerId == _worker.Id) {
						providedNeed.allocatedWorkerId = 0u;
					}
				}
				std::cout << "Needs restored (fun)" << std::endl;
			}
		}
		if (needProvider.providedNeedId == inf::djb_hash(Definitions::NeedCategory_Sleep)) {
			_worker.needs.sleep += _delta * needProvider.providedNeedRate;
			if (_worker.needs.sleep >= Definitions::BaseNeedMax_Sleep) {
				_worker.needs.sleep = Definitions::BaseNeedMax_Sleep;
				_worker.state = WorkerInstance::WorkerState::Idle;
				_worker.restoringNeedProviderId = 0u;
				for (BuildingProvidedNeed& providedNeed : needProvider.providedNeeds) {
					if (providedNeed.allocatedWorkerId == _worker.Id) {
						providedNeed.allocatedWorkerId = 0u;
					}
				}
				std::cout << "Needs restored (sleep)" << std::endl;
			}
		}
		if (needProvider.providedNeedId == inf::djb_hash(Definitions::NeedCategory_Nutrition)) {
			_worker.needs.nutrition += _delta * needProvider.providedNeedRate;
			if (_worker.needs.nutrition >= Definitions::BaseNeedMax_Nutrition) {
				_worker.needs.nutrition = Definitions::BaseNeedMax_Nutrition;
				_worker.state = WorkerInstance::WorkerState::Idle;
				_worker.restoringNeedProviderId = 0u;
				for (BuildingProvidedNeed& providedNeed : needProvider.providedNeeds) {
					if (providedNeed.allocatedWorkerId == _worker.Id) {
						providedNeed.allocatedWorkerId = 0u;
					}
				}
				std::cout << "Needs restored (nutrition)" << std::endl;
			}
		}
	}

	void WorkerUpdateService::resetWorkerAfterCompletingJob(WorkerInstance& _worker, const JobInstance& _jobInstance) {
		// TODO: What happens if we have repeating jobs?
		_worker.hasAllocatedJob = false;
		_worker.allocatedJobId = 0u;
		_worker.state = WorkerInstance::WorkerState::Idle;
	}

	JobInstance& WorkerUpdateService::retrieveJob(EntityId _jobId) {
		for (JobInstance& _job : m_JobData.jobs) {
			if (_job.Id == _jobId) {
				return _job;
			}
		}

		throw std::logic_error("Cannot retrieve job by id " + std::to_string(_jobId));
	}
	const JobInstance& WorkerUpdateService::retrieveJob(EntityId _jobId) const {
		for (JobInstance& _job : m_JobData.jobs) {
			if (_job.Id == _jobId) {
				return _job;
			}
		}

		throw std::logic_error("Cannot retrieve job by id " + std::to_string(_jobId));
	}

	BuildingInstance& WorkerUpdateService::retrieveBuilding(EntityId _buildingId) {
		for (BuildingInstance& _building : m_BuildingData.buildings) {
			if (_building.Id == _buildingId) {
				return _building;
			}
		}
		throw std::logic_error("Cannot retrieve building by id " + std::to_string(_buildingId));
	}
	const BuildingInstance& WorkerUpdateService::retrieveBuilding(EntityId _buildingId) const {
		for (const BuildingInstance& _building : m_BuildingData.buildings) {
			if (_building.Id == _buildingId) {
				return _building;
			}
		}
		throw std::logic_error("Cannot retrieve building by id " + std::to_string(_buildingId));
	}

}
