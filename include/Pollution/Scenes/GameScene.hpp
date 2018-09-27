#ifndef INCLUDED_POLLUTION_SCENES_GAME_SCENE_HPP_
#define INCLUDED_POLLUTION_SCENES_GAME_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Infrastructure/InputManager.hpp>
#include <Pollution/Infrastructure/ConfigurationManager.hpp>
#include <Pollution/DataStructures/WorldData.hpp>
#include <Pollution/GameObjects/WorldObject.hpp>
#include <Pollution/Services/Interfaces/IWorldUpdateService.hpp>
#include <Pollution/Services/Interfaces/IWorldInteractionService.hpp>
#include <Infrastructure/TextureManager.hpp>

#include <vector>
#include <Infrastructure/FontManager.hpp>
#include <Infrastructure/Services/Interfaces/IResourceService.hpp>
#include <Pollution/DataStructures/BuildingData.hpp>
#include <Pollution/DataStructures/AnimationData.hpp>
#include <Pollution/GameObjects/BuildingObject.hpp>

namespace pol {
	
	class GameScene : public inf::Scene {
	public:
		GameScene(inf::InputManager& _inputManager, inf::FontManager& _fontManager, inf::TextureManager& _textureManager, inf::IResourceService& _resourceService, ConfigurationManager& _configurationManager, IWorldUpdateService& _worldUpdateService, IWorldInteractionService& _worldInteractionService);
		~GameScene(void) override;

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

		void initialise(const WorldDataInitialisationPackage& _worldInitialisationPackage);

		WorldObject& getWorldObject(void);
		bool handleClickingUi(const sf::Event& _event);
		bool handlePlacingBuilding(const sf::Event& _event);

	private:
		inf::InputManager& m_InputManager;
		inf::FontManager& m_FontManager;
		inf::TextureManager& m_TextureManager;
		inf::IResourceService& m_ResourceService;
		ConfigurationManager& m_Config;

		WorldData m_WorldData;
		WorldObject m_WorldObject;
		IWorldUpdateService& m_WorldUpdateService;
		IWorldInteractionService& m_WorldInteractionService;

		sf::Text m_GoldText;
		sf::Text m_SpecialText;
		sf::Text m_YearText;
		sf::Text m_AgeText;

		std::vector<sf::Text> m_BuildingTextThings;
		std::vector<BuildingData> m_BuildingDataUI;
		std::vector<BuildingObject> m_UIBuildingObjects;
		std::vector<BuildingObject> m_BuildingObjects;
		std::vector<Animation> m_AnimationPrototypes;
		std::vector<sf::Color> m_DistinctColours;

		int m_ActiveBuildingGhostIndex{ -1 };

		int m_ResourceChangedCallbackId;
		float m_Accumulation{0.0f};
	};

}

#endif // INCLUDED_POLLUTION_SCENES_GAME_SCENE_HPP_