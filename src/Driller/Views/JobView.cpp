#include <Driller/Views/JobView.hpp>
#include <Driller/Infrastructure/Definitions.hpp>

namespace drl {

	JobView::JobView(inf::TextureManager& _textureManager, const JobData& _jobData) :
		m_TextureManager(_textureManager),
		m_JobData(_jobData) {
		
	}
	JobView::~JobView(void) {
		
	}

	void JobView::update(float _delta) {
		
	}
	void JobView::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {

		const float JobCoordinateRadius(0.25f);
		sf::CircleShape jobCoordinates(JobCoordinateRadius);
		jobCoordinates.setOrigin(JobCoordinateRadius, JobCoordinateRadius);
		jobCoordinates.setFillColor(sf::Color(255, 255, 0, 185));

		const float JobPerformRadius(0.05f);
		sf::CircleShape jobPerform(JobPerformRadius);
		jobPerform.setOrigin(JobPerformRadius, JobPerformRadius);
		jobPerform.setFillColor(sf::Color(0, 255, 255, 185));

		sf::RectangleShape jobBounds;
		jobBounds.setFillColor(sf::Color::Transparent);
		jobBounds.setOutlineColor(sf::Color(0, 255, 0, 185));
		jobBounds.setOutlineThickness(0.01f);
		jobBounds.move(-Definitions::TileSize / 2.0f, 0.0f);

		for (const JobInstance& _job : m_JobData.jobs) {
			sf::RenderStates states(_states);
			states.transform.translate(static_cast<float>(_job.coordinates.x), static_cast<float>(_job.coordinates.y));
			jobBounds.setSize(sf::Vector2f(_job.bounds));
			_target.draw(jobBounds, states);
			states.transform.translate(0.0f, Definitions::TileSize / 2.0f);
			_target.draw(jobCoordinates, states);
			states.transform.translate(0.0f, Definitions::TileSize / 2.0f);
			states.transform.translate(_job.jobPerformOffset);
			_target.draw(jobPerform, states);
		}

	}
}
