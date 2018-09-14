#ifndef INCLUDED_INTRUSION_SCENES_GAME_UI_SCENE_HPP_
#define INCLUDED_INTRUSION_SCENES_GAME_UI_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/FontManager.hpp>
#include <Infrastructure/InputManager.hpp>

#include <Intrusion/Infrastructure/IntrusionConfigurationManager.hpp>
#include <Intrusion/Services/ILevelResourceService.hpp>

#include <map>

namespace itr {
	class GameUiScene : public inf::Scene {
	public:
		GameUiScene(inf::FontManager& _fontManager, inf::TextureManager& _textureManager, inf::InputManager& _inputManager, IntrusionConfigurationManager& _configurationManager, ILevelResourceService& _levelResourceService);
		~GameUiScene(void);

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

	protected:
		void updateResourceText(const std::string& _resourceName);

	private:
		inf::FontManager& m_FontManager;
		inf::TextureManager& m_TextureManager;
		inf::InputManager& m_InputManager;
		itr::IntrusionConfigurationManager& m_ConfigurationManager;
		ILevelResourceService& m_LevelResourceService;

		std::map<std::string, sf::Text> m_ResourceTexts;
	};

}

#endif // INCLUDED_INTRUSION_SCENES_GAME_UI_SCENE_HPP_