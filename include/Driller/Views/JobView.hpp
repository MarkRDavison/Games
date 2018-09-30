#ifndef INCLUDED_DRILLER_VIEWS_JOB_VIEW_HPP_
#define INCLUDED_DRILLER_VIEWS_JOB_VIEW_HPP_

#include <Driller/Views/View.hpp>
#include <Driller/DataStructures/JobData.hpp>
#include <Infrastructure/TextureManager.hpp>

namespace drl {
	
	class JobView : public View {
	public:
		JobView(inf::TextureManager& _textureManager, const JobData& _jobData);
		~JobView(void) override;

		void update(float _delta) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

	private:
		inf::TextureManager& m_TextureManager;
		const JobData& m_JobData;
	};

}

#endif // INCLUDED_DRILLER_VIEWS_JOB_VIEW_HPP_