#ifndef INCLUDED_POLLUTION_SCENES_GAME_SCENE_HPP_
#define INCLUDED_POLLUTION_SCENES_GAME_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Pollution/Infrastructure/ConfigurationManager.hpp>
#include <Pollution/DataStructures/WorldData.hpp>

namespace pol {
	
	class GameScene : public inf::Scene {
	public:
		GameScene(inf::InputManager& _inputManager, ConfigurationManager& _configurationManager);
		~GameScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

		void initialise(const WorldDataInitialisationPackage& _worldInitialisationPackage);

	private:
		inf::InputManager& m_InputManager;
		ConfigurationManager& m_Config;

		WorldData m_World;
	};

}

#endif // INCLUDED_POLLUTION_SCENES_GAME_SCENE_HPP_