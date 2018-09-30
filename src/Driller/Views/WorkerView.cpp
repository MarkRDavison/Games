#include <Driller/Views/WorkerView.hpp>
#include <Driller/Infrastructure/Definitions.hpp>

namespace drl {

	WorkerView::WorkerView(const WorkerData& _workerData) :
		m_WorkerData(_workerData) {
		
	}
	WorkerView::~WorkerView(void) {
		
	}

	void WorkerView::update(float _delta) {
		
	}
	void WorkerView::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {

		sf::RectangleShape r({ Definitions::TileSize / 2.0f, Definitions::TileSize } );
		r.setOrigin(Definitions::TileSize / 4.0f, 0.0f);
		r.setFillColor(sf::Color(255, 0, 255, 200));

		for (const WorkerInstance& worker : m_WorkerData.workers) {
			sf::RenderStates states(_states);
			states.transform.translate(worker.position);
			_target.draw(r, states);
		}
	}

}
