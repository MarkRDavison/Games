#ifndef INCLUDED_DRILLER_SERVICES_WORKER_CLASS_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_WORKER_CLASS_SERVICE_HPP_

#include <Driller/Services/Interfaces/IWorkerClassService.hpp>
#include <Infrastructure/Services/Interfaces/IResourceService.hpp>
#include <map>

namespace drl {

	class WorkerClassService : public IWorkerClassService {
	public:
		WorkerClassService(inf::IResourceService& _resourceService);
		~WorkerClassService(void) override;

		void registerPrototypeToResourceClass(const WorkerPrototypeId& _prototypeId, const std::string& _resource) override;
		bool isPrototypeRegistered(const WorkerPrototypeId& _prototypeId) override;

		void increaseClassMaximum(const WorkerPrototypeId& _prototypeId, int _amount) override;
		void increaseClass(const WorkerPrototypeId& _prototypeId, int _amount) override;
		bool canIncreaseClass(const WorkerPrototypeId& _prototypeId, int _amount) override;

		void decreaseClassMaximum(const WorkerPrototypeId& _prototypeId, int _amount) override;
		void decreaseClass(const WorkerPrototypeId& _prototypeId, int _amount) override;

	private:
		inf::IResourceService& m_ResourceService;

		std::map<WorkerPrototypeId, std::string> m_PrototypeResourceMap;
	};

}

#endif // INCLUDED_DRILLER_SINCLUDED_DRILLER_SERVICES_WORKER_CLASS_SERVICE_HPP_ERVICES_INTERFACES_I_WORKER_CLASS_SERVICE_HPP_