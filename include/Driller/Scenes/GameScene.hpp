#ifndef INCLUDED_DRILLER_SCENES_GAME_SCENE_HPP_
#define INCLUDED_DRILLER_SCENES_GAME_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Infrastructure/Interfaces/IConfigurationManager.hpp>

#include <Driller/Services/Interfaces/ISceneChangeService.hpp>
#include <Driller/Services/Interfaces/IGameCommandService.hpp>

#include <Driller/Core/Game.hpp>

#include <Driller/Views/TerrainView.hpp>
#include <Driller/Views/BuildingView.hpp>
#include <Driller/Views/JobView.hpp>
#include <Driller/Views/WorkerView.hpp>
#include <Driller/Views/ShuttleView.hpp>

namespace drl {

	class GameScene : public inf::Scene {
	public:
		GameScene(inf::IConfigurationManager& _config, inf::InputManager& _inputManager, ISceneChangeService& _sceneChangeService, IGameCommandService& _gameCommandService, Game& _game, TerrainView& _terrainView, BuildingView& _buildingView, JobView& _jobView, WorkerView& _workerView, ShuttleView& _shuttleView);
		~GameScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event & _event) override;
		void draw(sf::RenderTarget & _target, sf::RenderStates _states, float _alpha) const override;
		
		bool handleMouseButton(sf::Mouse::Button _button, const int _x, const int _y);

	private:
		inf::IConfigurationManager& m_Config;
		inf::InputManager& m_InputManager;
		ISceneChangeService& m_SceneChangeService;
		IGameCommandService& m_GameCommandService;
		Game& m_Game;
		TerrainView& m_TerrainView;
		BuildingView& m_BuildingView;
		WorkerView& m_WorkerView;
		JobView& m_JobView;
		ShuttleView& m_ShuttleView;

		int m_ActiveBuilding{ -1 };
		
		sf::Vector2f m_CameraOffset;
	};

}

#endif // INCLUDED_DRILLER_SCENES_GAME_SCENE_HPP_