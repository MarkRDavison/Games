#include <Driller/Views/ShuttleView.hpp>

namespace drl {
	ShuttleView::ShuttleView(const ShuttleData& _shuttleData) :
		m_ShuttleData(_shuttleData) {
		
	}
	ShuttleView::~ShuttleView(void) {
		
	}
	void ShuttleView::update(float _delta) {
		
	}
	void ShuttleView::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		const float SizeX = 3.0f;
		const float SizeY = 2.0f;

		sf::RectangleShape r({ SizeX , SizeY });
		r.setOrigin(SizeX / 2.0f, SizeY);
		r.setFillColor(sf::Color::Blue);
		_states.transform.translate(0.0f, Definitions::TileSize);
		for (const ShuttleInstance& shuttle : m_ShuttleData.shuttles) {
			sf::RenderStates states(_states);
			states.transform.translate(shuttle.position);

			_target.draw(r, states);
		}
	}
}