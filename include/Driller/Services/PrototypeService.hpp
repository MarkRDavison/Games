#ifndef INCLUDED_DRILLER_SERVICES_PROTOTYPE_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_PROTOTYPE_SERVICE_HPP_

#include <Driller/Services/Interfaces/IPrototypeService.hpp>
#include <Utility/Hash.hpp>
#include <map>
#include "Interfaces/IIdentificationService.hpp"

namespace drl {

	template <typename TPrototype, typename TInstance, typename TPrototypeId>
	class PrototypeService : public IPrototypeService<TPrototype, TInstance, TPrototypeId> {
	public:
		PrototypeService(IIdentificationService& _identificationService) :
			m_IdentificationService(_identificationService) {
			
		}
		~PrototypeService(void) override { }
		
		TPrototypeId getPrototypeId(const std::string& _prototypeName) const override {
			return inf::djb_hash(_prototypeName.c_str());
		}

		void registerPrototype(const std::string& _prototypeName, const TPrototype& _prototype) override {
			const TPrototypeId id = getPrototypeId(_prototypeName);
			if (m_NamePrototypeMap.find(id) == m_NamePrototypeMap.end()) {
				m_PrototypeIdNameMap[id] = _prototypeName;
			}
			registerPrototype(id, _prototype);
		}
		void registerPrototype(const TPrototypeId& _prototypeId, const TPrototype& _prototype) override {
			if (!isPrototypeRegistered(_prototypeId)) {
				m_NamePrototypeMap[_prototypeId] = _prototype;
			}
		}

		const TPrototype& getPrototype(const std::string& _prototypeName) override {
			return getPrototype(getPrototypeId(_prototypeName));
		}
		const TPrototype& getPrototype(const TPrototypeId& _prototypeId) override {
			if (isPrototypeRegistered(_prototypeId)) {
				return m_NamePrototypeMap[_prototypeId];
			}

			throw std::logic_error("Prototype is not registered.");
		}

		TInstance createInstance(const std::string& _prototypeName) override {
			return createInstance(getPrototypeId(_prototypeName));
		}
		TInstance createInstance(const TPrototypeId& _prototypeId) override = 0;

		bool isPrototypeRegistered(const std::string& _prototypeName) const override {
			return isPrototypeRegistered(getPrototypeId(_prototypeName));
		}
		bool isPrototypeRegistered(const TPrototypeId& _prototypeId) const override {
			return m_NamePrototypeMap.find(_prototypeId) != m_NamePrototypeMap.end();
		}

	protected:
		IIdentificationService& m_IdentificationService;

		std::map<TPrototypeId, std::string> m_PrototypeIdNameMap;
		std::map<TPrototypeId, TPrototype> m_NamePrototypeMap;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_PROTOTYPE_SERVICE_HPP_