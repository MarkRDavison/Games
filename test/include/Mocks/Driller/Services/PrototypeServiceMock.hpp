#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_PROTOTYPE_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_PROTOTYPE_SERVICE_MOCK_HPP_

#include <Driller/DataStructures/BuildingInstance.hpp>
#include <Driller/DataStructures/BuildingPrototype.hpp>
#include <Driller/DataStructures/JobInstance.hpp>
#include <Driller/DataStructures/JobPrototype.hpp>
#include <Driller/DataStructures/ShuttleInstance.hpp>
#include <Driller/DataStructures/ShuttlePrototype.hpp>
#include <Driller/DataStructures/WorkerInstance.hpp>
#include <Driller/DataStructures/WorkerPrototype.hpp>
#include <Driller/Services/Interfaces/IPrototypeService.hpp>
#include <functional>

namespace drl {

	template <typename TPrototype, typename TInstance, typename TPrototypeId>
	class PrototypeServiceMock : public IPrototypeService<TPrototype, TInstance, TPrototypeId> {
	public:
		~PrototypeServiceMock(void) override {}

		TPrototypeId getPrototypeId(const std::string& _prototypeName) const override {
			if (getPrototypeIdCallback) {
				return getPrototypeIdCallback(_prototypeName);
			}

			return {};
		}

		void registerPrototype(const std::string& _prototypeName, const TPrototype& _buildingPrototype) override {
			if (registerPrototypeByNameCallback) {
				registerPrototypeByNameCallback(_prototypeName, _buildingPrototype);
			}
		}
		void registerPrototype(const TPrototypeId& _prototypeId, const TPrototype& _buildingPrototype) override {
			if (registerPrototypeByIdCallback) {
				registerPrototypeByIdCallback(_prototypeId, _buildingPrototype);
			}
		}

		const TPrototype& getPrototype(const std::string& _prototypeName) override {
			if (getPrototypeByNameCallback) {
				return getPrototypeByNameCallback(_prototypeName);
			}

			return defaultPrototype;
		}
		const TPrototype& getPrototype(const TPrototypeId& _prototypeId) override {
			if (getPrototypeByIdCallback) {
				return getPrototypeByIdCallback(_prototypeId);
			}

			return defaultPrototype;
		}

		TInstance createInstance(const std::string& _prototypeName) override {
			if (createInstanceByNameCallback) {
				return createInstanceByNameCallback(_prototypeName);
			}

			return {};
		}
		TInstance createInstance(const TPrototypeId& _prototypeId) override {
			if (createInstanceByIdCallback) {
				return createInstanceByIdCallback(_prototypeId);
			}

			return {};
		}

		bool isPrototypeRegistered(const TPrototypeId& _prototypeId) const override {
			if (isPrototypeRegisteredByIdCallback) {
				return isPrototypeRegisteredByIdCallback(_prototypeId);
			}

			return false;
		}
		bool isPrototypeRegistered(const std::string& _prototypeName) const override {
			if (isPrototypeRegisteredByNameCallback) {
				return isPrototypeRegisteredByNameCallback(_prototypeName);
			}

			return false;
		}

		TPrototype defaultPrototype{};

		std::function<TPrototypeId(const std::string&)> getPrototypeIdCallback;
		std::function<void(const std::string&, const TPrototype&)> registerPrototypeByNameCallback;
		std::function<void(const TPrototypeId&, const TPrototype&)> registerPrototypeByIdCallback;
		std::function<const TPrototype&(const std::string&)> getPrototypeByNameCallback;
		std::function<const TPrototype&(const TPrototypeId&)> getPrototypeByIdCallback;
		std::function<TInstance(const std::string&)> createInstanceByNameCallback;
		std::function<TInstance(const TPrototypeId&)> createInstanceByIdCallback;
		std::function<bool(const TPrototypeId&)> isPrototypeRegisteredByIdCallback;
		std::function<bool(const std::string&)> isPrototypeRegisteredByNameCallback;
	};

	using BuildingPrototypeServiceMock = PrototypeServiceMock<BuildingPrototype, BuildingInstance, BuildingPrototypeId>;
	using JobPrototypeServiceMock = PrototypeServiceMock<JobPrototype, JobInstance, JobPrototypeId>;
	using ShuttlePrototypeServiceMock = PrototypeServiceMock<ShuttlePrototype, ShuttleInstance, ShuttlePrototypeId>;
	using WorkerPrototypeServiceMock = PrototypeServiceMock<WorkerPrototype, WorkerInstance, WorkerPrototypeId>;

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_PROTOTYPE_SERVICE_MOCK_HPP_