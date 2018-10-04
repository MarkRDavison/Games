#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_WORKER_CLASS_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_WORKER_CLASS_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IWorkerClassService.hpp>
#include <functional>

namespace drl {
	
	class WorkerClassServiceMock : public IWorkerClassService {
	public:
		~WorkerClassServiceMock(void) override {}

		void registerPrototypeToResourceClass(const WorkerPrototypeId& _prototypeId, const std::string& _resource) override {
			if (registerPrototypeToResourceClassCallback) {
				registerPrototypeToResourceClass(_prototypeId, _resource);
			}
		}
		bool isPrototypeRegistered(const WorkerPrototypeId& _prototypeId) override {
			if (isPrototypeRegisteredCallback) {
				isPrototypeRegisteredCallback(_prototypeId);
			}

			return false;
		}

		void increaseClassMaximum(const WorkerPrototypeId& _prototypeId, int _amount) override {
			if (increaseClassMaximumCallback) {
				increaseClassMaximumCallback(_prototypeId, _amount);
			}
		}
		void increaseClass(const WorkerPrototypeId& _prototypeId, int _amount) override{
			if (increaseClassCallback) {
				increaseClassCallback(_prototypeId, _amount);
			}
		}
		bool canIncreaseClass(const WorkerPrototypeId& _prototypeId, int _amount) override{
			if (canIncreaseClassCallback) {
				return canIncreaseClassCallback(_prototypeId, _amount);
			}

			return false;
		}

		void decreaseClassMaximum(const WorkerPrototypeId& _prototypeId, int _amount) override {
			if (decreaseClassMaximumCallback) {
				decreaseClassMaximum(_prototypeId, _amount);
			}
		}
		void decreaseClass(const WorkerPrototypeId& _prototypeId, int _amount) override {
			if (decreaseClassCallback) {
				decreaseClassCallback(_prototypeId, _amount);
			}
		}

		std::function<void(const WorkerPrototypeId&, const std::string&)> registerPrototypeToResourceClassCallback;
		std::function<bool(const WorkerPrototypeId&)> isPrototypeRegisteredCallback;
		std::function<void(const WorkerPrototypeId&, int)> increaseClassMaximumCallback;
		std::function<void(const WorkerPrototypeId&, int)> increaseClassCallback;
		std::function<bool(const WorkerPrototypeId&, int)> canIncreaseClassCallback;

		std::function<void(const WorkerPrototypeId&, int)> decreaseClassMaximumCallback;
		std::function<void(const WorkerPrototypeId&, int)> decreaseClassCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_WORKER_CLASS_SERVICE_MOCK_HPP_