#ifndef INCLUDED_INTRUSION_SCENES_START_SCENE_HPP_
#define INCLUDED_INTRUSION_SCENES_START_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Infrastructure/FontManager.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/Gui/BasicButton.hpp>

#include <Intrusion/Infrastructure/IntrusionConfigurationManager.hpp>
#include <Infrastructure/Gui/TextBox.hpp>

namespace itr {
	class StartScene : public inf::Scene {
	public:
		StartScene(inf::FontManager& _fontManager, inf::TextureManager& _textureManager, itr::IntrusionConfigurationManager& _configurationManager, inf::InputManager& _inputManager);
		~StartScene(void);

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

	protected:
		void updateUiPositions(void);

	private:
		inf::FontManager& m_FontManager;
		inf::TextureManager& m_TextureManager;
		itr::IntrusionConfigurationManager& m_ConfigurationManager;
		inf::InputManager& m_InputManager;
	
		sf::Sprite m_IconSprite;

		inf::BasicButton m_TestButton1;
		inf::BasicButton m_TestButton2;
		inf::TextBox m_TextBox1;
	};
}

#endif // INCLUDED_INTRUSION_SCENES_START_SCENE_HPP_