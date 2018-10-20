#include <Driller/Views/WorkerView.hpp>
#include <Driller/Infrastructure/Definitions.hpp>
#include <Utility/Hash.hpp>

namespace drl {

	WorkerView::WorkerView(const WorkerData& _workerData) :
		m_WorkerData(_workerData) {
		
	}
	WorkerView::~WorkerView(void) {
		
	}

	void WorkerView::update(float _delta) {
		
	}

	sf::Color getWorkerColor(const WorkerInstance& _worker) {
		if (_worker.prototypeId == inf::djb_hash(Definitions::WorkerPrototypeName_Builder)) {
			return sf::Color::Cyan;
		}
		if (_worker.prototypeId == inf::djb_hash(Definitions::WorkerPrototypeName_Miner)) {
			return sf::Color::Yellow;
		}
		if (_worker.prototypeId == inf::djb_hash(Definitions::WorkerPrototypeName_Refiner)) {
			return sf::Color::Magenta;
		}

		return sf::Color::White;
	}

	void WorkerView::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {

		sf::RectangleShape r({ Definitions::TileSize / 2.0f, Definitions::TileSize } );
		r.setOrigin(Definitions::TileSize / 4.0f, 0.0f);
		r.setFillColor(sf::Color(255, 0, 255, 200));

		for (const WorkerInstance& worker : m_WorkerData.workers) {
			sf::RenderStates states(_states);
			r.setFillColor(getWorkerColor(worker));
			states.transform.translate(worker.position);
			_target.draw(r, states);
		}
	}

}
