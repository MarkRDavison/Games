#include <Castle/Scenes/DebugOverlayScene.hpp>

#define FONT_NAME "source_code_pro_regular"

namespace castle {

	DebugOverlayScene::DebugOverlayScene(inf::FontManager& _fontManager) :
		inf::Scene("castle::DebugOverlayScene "),
		m_FontManager(_fontManager) {
		
	}
	DebugOverlayScene::~DebugOverlayScene(void) {
		
	}

	void DebugOverlayScene::update(float _delta) {
		
	}
	bool DebugOverlayScene::handleEvent(const sf::Event& _event) {
		return false;
	}
	void DebugOverlayScene::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
		auto& v = _target.getView();
		_target.setView(_target.getDefaultView());

		sf::Text t;
		t.setFont(m_FontManager.getFont(FONT_NAME));
		t.setFillColor(sf::Color::White);
		t.setOutlineColor(sf::Color::Black);
		t.setOutlineThickness(2.0f);
		t.setCharacterSize(16);

		for (unsigned i = 0; i < 5; ++i) {
			_states.transform.translate(0.0f, 16.0f);
			t.setString("THIS IS SOME TEXT " + std::to_string(i));


			_target.draw(t, _states);
		}

		_target.setView(v);

	}

}