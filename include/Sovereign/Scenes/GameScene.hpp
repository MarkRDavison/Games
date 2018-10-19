#ifndef INCLUDED_SOVEREIGN_SCENES_GAME_SCENE_HPP_
#define INCLUDED_SOVEREIGN_SCENES_GAME_SCENE_HPP_

#include <Sovereign/Core/Game.hpp>
#include <Sovereign/Services/Interfaces/ISceneChangeService.hpp>
#include <Infrastructure/Scene.hpp>
#include <Infrastructure/Interfaces/IConfigurationManager.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/TextureManager.hpp>

namespace sov {

	class GameScene : public inf::Scene {
	public:
		GameScene(inf::IConfigurationManager& _config, inf::InputManager& _inputManager, inf::TextureManager& _textureManager, ILogService& _logService, ISceneChangeService& _sceneChangeService, Game& _game);
		~GameScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event & _event) override;
		void draw(sf::RenderTarget & _target, sf::RenderStates _states, float _alpha) const override;

		sf::Vector2f convertEventCoordinatesToLocalGameCoordinates(const sf::Vector2i& _coordinates) const;

		void zoomViewAt(const sf::Vector2i& _pixel, float _zoom);

		bool handlePickup(const MoveableEntity& me) const;
		bool handleMineStart(const MoveableEntity& me) const;

		void resizeView(void);

		void regenerateTerrain(void);

	private:
		inf::IConfigurationManager& m_Config;
		inf::InputManager& m_InputManager;
		inf::TextureManager& m_TextureManager;
		ILogService& m_LogService;
		ISceneChangeService& m_SceneChangeService;
		sf::VertexArray cells;

		sf::Color m_MineColor{ sf::Color::Blue };
		sf::Color m_PickupColor{ sf::Color::Cyan };


		Game& m_Game;
		sf::View m_View;

		sf::Vector2f m_PanningAnchor;

		bool m_Panning{ false };
		float m_Zoom{ 1.0f };
		const float m_ZoomSensitivity{ 1.25f };
	};

}

#endif // INCLUDED_SOVEREIGN_SCENES_GAME_SCENE_HPP_