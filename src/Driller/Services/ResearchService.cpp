#include <Driller/Services/ResearchService.hpp>
#include <Utility/Hash.hpp>
#include <algorithm>
#include <cassert>

namespace drl {

	ResearchService::ResearchService(ResearchData& _researchData) :
		m_ResearchData(_researchData) {
		
	}
	ResearchService::~ResearchService(void){

	}


	void ResearchService::registerResearchCategory(const std::string& _researchCategoryName) {
		registerResearchCategory(inf::djb_hash(_researchCategoryName.c_str()));
	}
	void ResearchService::registerResearchCategory(const ResearchId& _researchCategory) {
		assert(std::find_if(m_ResearchData.categories.begin(), m_ResearchData.categories.end(), [&](const ResearchCategory& _category) -> bool { return _researchCategory == _category.categoryId; }) == m_ResearchData.categories.end());

		ResearchCategory category{};
		category.categoryId = _researchCategory;
		m_ResearchData.categories.emplace_back(category);
	}

	void ResearchService::registerResearchInstance(const std::string& _researchCategoryName, const ResearchInstance& _researchInstance) {
		registerResearchInstance(inf::djb_hash(_researchCategoryName.c_str()), _researchInstance);
	}
	void ResearchService::registerResearchInstance(const ResearchId& _researchCategory, const ResearchInstance& _researchInstance) {
		auto& categoryIterator = std::find_if(m_ResearchData.categories.begin(), m_ResearchData.categories.end(), [&](const ResearchCategory& _category) -> bool { return _researchCategory == _category.categoryId; });
		assert(categoryIterator != m_ResearchData.categories.end());

		ResearchCategory& category = *categoryIterator;
		category.instances.emplace_back(_researchInstance);
	}

	bool ResearchService::isResearchOutstanding(const std::string& _researchCategoryName) const {
		return isResearchOutstanding(inf::djb_hash(_researchCategoryName.c_str()));
	}
	bool ResearchService::isResearchOutstanding(const ResearchId& _researchCategory) const {
		auto& categoryIterator = std::find_if(m_ResearchData.categories.begin(), m_ResearchData.categories.end(), [&](const ResearchCategory& _category) -> bool { return _researchCategory == _category.categoryId; });
		if (categoryIterator == m_ResearchData.categories.end()) {
			return false;
		}

		const ResearchCategory& category = *categoryIterator;

		return !category.instances.empty();
	}

	const ResearchInstance& ResearchService::getOutstandingResearchInstance(const std::string& _researchCategoryName) const {
		return getOutstandingResearchInstance(inf::djb_hash(_researchCategoryName.c_str()));
	}
	const ResearchInstance& ResearchService::getOutstandingResearchInstance(const ResearchId& _researchCategory) const {
		assert(isResearchOutstanding(_researchCategory));
		auto& categoryIterator = std::find_if(m_ResearchData.categories.begin(), m_ResearchData.categories.end(), [&](const ResearchCategory& _category) -> bool { return _researchCategory == _category.categoryId; });

		const ResearchCategory& category = *categoryIterator;

		return category.instances.front();
	}

	void ResearchService::research(const std::string& _researchCategoryName) {
		research(inf::djb_hash(_researchCategoryName.c_str()));
	}
	void ResearchService::research(const ResearchId& _researchCategory) {
		assert(isResearchOutstanding(_researchCategory));
		auto& categoryIterator = std::find_if(m_ResearchData.categories.begin(), m_ResearchData.categories.end(), [&](const ResearchCategory& _category) -> bool { return _researchCategory == _category.categoryId; });

		ResearchCategory& category = *categoryIterator;

		const ResearchInstance& instance = category.instances.front();

		if (instance.callback) {
			instance.callback(_researchCategory, instance.level);
		}

		category.instances.erase(category.instances.begin());
	}
}
