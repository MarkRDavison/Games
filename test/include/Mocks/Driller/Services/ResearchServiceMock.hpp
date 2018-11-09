#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_RESEARCH_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_RESEARCH_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/IResearchService.hpp>
#include <Utility/TestSignal.hpp>
#include <Utility/Hash.hpp>

namespace drl {

	class ResearchServiceMock : public IResearchService {
	public:
		~ResearchServiceMock(void) override {}

		void registerResearchCategory(const std::string& _researchCategoryName) override {
			registerResearchCategory(inf::djb_hash(_researchCategoryName));
		}
		void registerResearchCategory(const ResearchId& _researchCategory) override {
			registerResearchCategoryCallback(_researchCategory);
		}

		void registerResearchInstance(const std::string& _researchCategoryName, const ResearchInstance& _researchInstance) override {
			registerResearchInstance(inf::djb_hash(_researchCategoryName), _researchInstance);
		}
		void registerResearchInstance(const ResearchId& _researchCategory, const ResearchInstance& _researchInstance) override {
			registerResearchInstanceCallback(_researchCategory, _researchInstance);
		}

		bool isResearchOutstanding(const std::string& _researchCategoryName) const override {
			return isResearchOutstanding(inf::djb_hash(_researchCategoryName));
		}
		bool isResearchOutstanding(const ResearchId& _researchCategory) const override {
			return isResearchOutstandingCallback(_researchCategory);
		}

		const ResearchInstance& getOutstandingResearchInstance(const std::string& _researchCategoryName) const override {
			return getOutstandingResearchInstance(inf::djb_hash(_researchCategoryName));
		}
		const ResearchInstance& getOutstandingResearchInstance(const ResearchId& _researchCategory) const override {
			return getOutstandingResearchInstanceCallback(_researchCategory);
		}

		void research(const std::string& _researchCategoryName) override {
			research(inf::djb_hash(_researchCategoryName));
		}
		void research(const ResearchId& _researchCategory) override {
			researchCallback(_researchCategory);
		}


		inf::TestSignal<void, const ResearchId&> registerResearchCategoryCallback;
		inf::TestSignal<void, const ResearchId&, const ResearchInstance&> registerResearchInstanceCallback;
		inf::TestSignal<bool, const ResearchId&> isResearchOutstandingCallback;
		inf::TestSignal<const ResearchInstance&, const ResearchId&> getOutstandingResearchInstanceCallback;
		inf::TestSignal<void, const ResearchId&> researchCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_RESEARCH_SERVICE_MOCK_HPP_