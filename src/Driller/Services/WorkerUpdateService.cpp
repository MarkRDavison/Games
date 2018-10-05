#include <Driller/Services/WorkerUpdateService.hpp>
#include <Utility/VectorMath.hpp>
#include <iostream>
#include <string>

namespace drl {

	WorkerUpdateService::WorkerUpdateService(WorkerData& _workerData, JobData& _jobData, IJobCompletionService& _jobCompletionService) :
		m_WorkerData(_workerData),
		m_JobData(_jobData),
		m_JobCompletionService(_jobCompletionService){
		
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
		case WorkerInstance::WorkerState::WorkingJob:
			updateWorkingJobWorker(_worker, _delta);
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

	void WorkerUpdateService::populatePath(WorkerInstance& _worker) {
		JobInstance& job = retrieveJob(_worker.allocatedJobId);
		const sf::Vector2i current = sf::Vector2i(_worker.position);
		const sf::Vector2i target = job.coordinates;

		if (current == target) {
			_worker.state = WorkerInstance::WorkerState::WorkingJob;
			return;
		}

		_worker.path.path.isValid = true;
		_worker.path.path.nodes.emplace_back(inf::PathNode{ current.x, current.y, inf::PathNode::NodeType::Start });

		if (current.y != target.y) {
			_worker.path.path.nodes.emplace_back(inf::PathNode{ 0, current.y, inf::PathNode::NodeType::Standard });
			_worker.path.path.nodes.emplace_back(inf::PathNode{ 0, target.y, inf::PathNode::NodeType::Standard });			
		}

		_worker.path.path.nodes.emplace_back(inf::PathNode{ target.x, target.y, inf::PathNode::NodeType::End });
	}

	void WorkerUpdateService::followPath(WorkerInstance& _worker, float _delta) const {
		const inf::PathNode node = _worker.path.path.nodes.front();
		const sf::Vector2f currentNodeTarget(sf::Vector2i(node.x, node.y));

		const float distanceToTarget = inf::VectorMath::distance(_worker.position, currentNodeTarget);
		const float maxMovement = Definitions::BaseWorkerSpeed * _delta;

		if (distanceToTarget <= maxMovement) {
			_worker.path.path.nodes.erase(_worker.path.path.nodes.begin());
			_worker.position = currentNodeTarget;

			if (node.nodeType == inf::PathNode::NodeType::End) {
				_worker.path.path.isValid = false;
				_worker.state = WorkerInstance::WorkerState::WorkingJob;
				return;
			}

			const float remainingDelta = _delta - _delta * (distanceToTarget / maxMovement);

			followPath(_worker, remainingDelta);
		}
		else {
			_worker.position += inf::VectorMath::normalise(currentNodeTarget - _worker.position) * maxMovement;
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
			populatePath(_worker);
		} else if (!_worker.path.path.nodes.empty()) {
			followPath(_worker, _delta);
		}
	}

	void WorkerUpdateService::updateWorkingJobWorker(WorkerInstance& _worker, float _delta) {
		JobInstance& job = retrieveJob(_worker.allocatedJobId);

		job.workPerformed += _delta;
		if (job.workPerformed >= job.workRequired) {
			m_JobCompletionService.handleJobCompleted(job);

			if (m_JobCompletionService.isJobCompleteDelegateRegistered(job.prototypeId)) {
				JobCompleteDelegate& jobComplete = m_JobCompletionService.getJobCompleteDelegate(job.prototypeId);
				jobComplete(job);
			}

			resetWorkerAfterCompletingJob(_worker, job);
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

}
