#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_RESEARCH_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_RESEARCH_SERVICE_HPP_

#include <Driller/DataStructures/ResearchCategory.hpp>
#include <string>

namespace drl {

	class IResearchService {
	protected:
		virtual ~IResearchService(void) = 0;

	public:
		virtual void registerResearchCategory(const std::string& _researchCategoryName) = 0;
		virtual void registerResearchCategory(const ResearchId& _researchCategory) = 0;

		virtual void registerResearchInstance(const std::string& _researchCategoryName, const ResearchInstance& _researchInstance) = 0;
		virtual void registerResearchInstance(const ResearchId& _researchCategory, const ResearchInstance& _researchInstance) = 0;

		virtual bool isResearchOutstanding(const std::string& _researchCategoryName) const = 0;
		virtual bool isResearchOutstanding(const ResearchId& _researchCategory) const = 0;

		virtual const ResearchInstance& getOutstandingResearchInstance(const std::string& _researchCategoryName) const = 0;
		virtual const ResearchInstance& getOutstandingResearchInstance(const ResearchId& _researchCategory) const = 0;

		virtual void research(const std::string& _researchCategoryName) = 0;
		virtual void research(const ResearchId& _researchCategory) = 0;
	};

	inline IResearchService::~IResearchService(void) = default;

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_RESEARCH_SERVICE_HPP_