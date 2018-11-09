#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_WORKER_RECRUITMENT_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_WORKER_RECRUITMENT_SERVICE_HPP_
#include <Driller/DataStructures/ShuttleInstance.hpp>

namespace drl {
	
	class IWorkerRecruitmentService {
	public:
		virtual ~IWorkerRecruitmentService(void) = 0;

		virtual void recruitWorkers(const ShuttleInstance& _shuttle) = 0;
	};

	inline IWorkerRecruitmentService::~IWorkerRecruitmentService(void) = default;

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_WORKER_RECRUITMENT_SERVICE_HPP_