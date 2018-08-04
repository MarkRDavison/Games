#ifndef INCLUDED_CASTLE_SCENES_DEBUG_OVERLAY_SCENE_HPP_
#define INCLUDED_CASTLE_SCENES_DEBUG_OVERLAY_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Infrastructure/FontManager.hpp>

namespace castle {
	
	class DebugOverlayScene : public inf::Scene {
	public:
		DebugOverlayScene(inf::FontManager& _fontManager);
		~DebugOverlayScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	private:
		inf::FontManager& m_FontManager;
	};

}

#endif // INCLUDED_CASTLE_SCENES_DEBUG_OVERLAY_SCENE_HPP_