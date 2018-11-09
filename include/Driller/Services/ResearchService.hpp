#ifndef INCLUDED_DRILLER_SERVICES_RESEARCH_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_RESEARCH_SERVICE_HPP_

#include <Driller/Services/Interfaces/IResearchService.hpp>
#include <Driller/DataStructures/ResearchData.hpp>

namespace drl {


	class ResearchService : public IResearchService {
	public:
		ResearchService(ResearchData& _researchData);
		~ResearchService(void) override;

		void registerResearchCategory(const std::string& _researchCategoryName) override;
		void registerResearchCategory(const ResearchId& _researchCategory) override;

		void registerResearchInstance(const std::string& _researchCategoryName, const ResearchInstance& _researchInstance) override;
		void registerResearchInstance(const ResearchId& _researchCategory, const ResearchInstance& _researchInstance) override;

		bool isResearchOutstanding(const std::string& _researchCategoryName) const override;
		bool isResearchOutstanding(const ResearchId& _researchCategory) const override;

		const ResearchInstance& getOutstandingResearchInstance(const std::string& _researchCategoryName) const override;
		const ResearchInstance& getOutstandingResearchInstance(const ResearchId& _researchCategory) const override;

		void research(const std::string& _researchCategoryName) override;
		void research(const ResearchId& _researchCategory) override;

	private:
		ResearchData& m_ResearchData;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_RESEARCH_SERVICE_HPP_