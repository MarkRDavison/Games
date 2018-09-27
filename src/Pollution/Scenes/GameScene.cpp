#include <Pollution/Scenes/GameScene.hpp>
#include <Pollution/Infrastructure/Definitions.hpp>
#include <Utility/VectorMath.hpp>
#include <Utility/TextHelpers.hpp>
#include <Utility/Colour.hpp>
#include <iostream>

namespace pol {
	
	GameScene::GameScene(inf::InputManager& _inputManager, inf::FontManager& _fontManager, inf::TextureManager& _textureManager, inf::IResourceService& _resourceService, ConfigurationManager& _configurationManager, IWorldUpdateService& _worldUpdateService, IWorldInteractionService& _worldInteractionService) :
		inf::Scene("pol::GameScene"),
		m_InputManager(_inputManager),
		m_FontManager(_fontManager),
		m_TextureManager(_textureManager),
		m_ResourceService(_resourceService),
		m_Config(_configurationManager),
		m_WorldObject(m_WorldData),
		m_WorldUpdateService(_worldUpdateService),
		m_WorldInteractionService(_worldInteractionService),
		m_GoldText("Gold: 0", m_FontManager.getFont("DEBUG")),
		m_SpecialText("Special: 0", m_FontManager.getFont("DEBUG")),
		m_YearText("0-AD", m_FontManager.getFont("DEBUG")),
		m_AgeText("Age: 0", m_FontManager.getFont("DEBUG")),
		m_BuildingTextThings(Definitions::NumberBuildings, sf::Text("", m_FontManager.getFont("DEBUG"))) {

		m_BuildingDataUI.reserve(Definitions::NumberBuildings);
		m_AnimationPrototypes.reserve(Definitions::NumberBuildings);
		m_UIBuildingObjects.reserve(Definitions::NumberBuildings);

		m_GoldText.setFillColor(sf::Color::Yellow);
		m_SpecialText.setFillColor(sf::Color::Cyan);
		m_YearText.setFillColor(sf::Color::Green);
		m_AgeText.setFillColor(sf::Color::Magenta);

		m_ResourceChangedCallbackId = m_ResourceService.resourceChanged.registerCallback([&](const std::string& _resourceName) {
			if (_resourceName == Definitions::GoldResourceName) {
				m_GoldText.setString("Gold: " + std::to_string(m_ResourceService.getResource(Definitions::GoldResourceName)));
			}
			if (_resourceName == Definitions::SpecialResourceName) {
				m_SpecialText.setString("Special: " + std::to_string(m_ResourceService.getResource(Definitions::SpecialResourceName)));
			}
			if (_resourceName == Definitions::YearResourceName) {
				m_YearText.setString(std::to_string(m_ResourceService.getResource(Definitions::YearResourceName)) + "-AD");
			}
			if (_resourceName == Definitions::AgeResourceName) {
				m_AgeText.setString("Age: " + std::to_string(m_ResourceService.getResource(Definitions::AgeResourceName)));
			}
		});
		m_ResourceService.setResource(Definitions::GoldResourceName, 50);
		m_ResourceService.setResource(Definitions::AgeResourceName, 0);

		m_DistinctColours = {
			inf::Colour::DistinctMaroon,
			inf::Colour::DistinctBrown,
			inf::Colour::DistinctOlive,
			inf::Colour::DistinctTeal,
			inf::Colour::DistinctNavy,
			inf::Colour::DistinctRed,
			inf::Colour::DistinctOrange,
			inf::Colour::DistinctYellow,
			inf::Colour::DistinctLime,
			inf::Colour::DistinctGreen,
			inf::Colour::DistinctCyan,
			inf::Colour::DistinctBlue,
			inf::Colour::DistinctPurple,
			inf::Colour::DistinctMagenta,
			inf::Colour::DistinctGray,
			inf::Colour::DistinctPink,
			inf::Colour::DistinctApricot,
			inf::Colour::DistinctBeige,
			inf::Colour::DistinctMint,
			inf::Colour::DistinctLavender,
		};

		for (unsigned i = 0; i < m_BuildingTextThings.size(); ++i) {
			unsigned colorIndex = rand() % m_DistinctColours.size();
			const sf::Color col = m_DistinctColours[colorIndex];
			m_DistinctColours.erase(m_DistinctColours.begin() + colorIndex);
			sf::Text& text = m_BuildingTextThings[i];
			text.setString(std::to_string(i));
			text.setFillColor(col);
			text.setCharacterSize(48);
			inf::TextHelpers::centerText(text);

			
			BuildingData& data = m_BuildingDataUI.emplace_back();
			data.age = i;
			data.animationName = "Building_" + std::to_string(i);
			data.dropRate = Definitions::YearAccumulationRate;
			data.color = col;
			{
				inf::ResourceBundle::Resource costRes{};
				costRes.name = Definitions::GoldResourceName;
				costRes.amount = 25 * (i + 1) * (i + 1) * (i + 1);
				data.cost.resources.push_back(costRes);
			}
			if (i == m_BuildingTextThings.size() - 1) {
				// require special resource for last building
				inf::ResourceBundle::Resource costRes{};
				costRes.name = Definitions::SpecialResourceName;
				costRes.amount = 5;
				data.cost.resources.push_back(costRes);
			}


			{
				inf::ResourceBundle::Resource dropRes{};
				dropRes.name = Definitions::GoldResourceName;
				dropRes.amount = 5 * (i + 1) * (i + 1);
				data.drops.resources.push_back(dropRes);
			}
			if (i == m_BuildingTextThings.size() - 2) {
				// drop special resource required for last building
				inf::ResourceBundle::Resource dropRes{};
				dropRes.name = Definitions::SpecialResourceName;
				dropRes.amount = 1;
				data.drops.resources.push_back(dropRes);
			}

			Animation& animation = m_AnimationPrototypes.emplace_back();
			for (int j = 0; j < 8; ++j) {
				Animation::Frame& frame = animation.frames.emplace_back();
				frame.duration = 0.05f + static_cast<float>(rand() % 100) / 1000.0f;
				frame.bounds = sf::IntRect(j * 64, i * 64, 64, 64);
			}

			m_UIBuildingObjects.emplace_back(&data, &m_AnimationPrototypes.back(), m_TextureManager.getTexture(Definitions::BuildingTextureName));
		}

		
	}
	GameScene::~GameScene(void) {

	}

	void GameScene::update(float _delta) {
		m_WorldUpdateService.update(_delta, m_WorldData);
		m_Accumulation += _delta;
		if (m_Accumulation >= Definitions::YearAccumulationRate) {
			m_Accumulation -= Definitions::YearAccumulationRate;
			m_ResourceService.updateResource(Definitions::YearResourceName, 1);
		}
		for (BuildingData& bd : m_BuildingDataUI) {
			bd.accumulatedAnimationTime += _delta; // TODO: Modifying the prototypes seems bad
		}
		for (BuildingObject& buildingObject : m_UIBuildingObjects) {
			buildingObject.update(_delta);
		}
		for (BuildingObject& bo : m_BuildingObjects) {
			bo.update(_delta);
		}
	}
	
	bool GameScene::handleEvent(const sf::Event& _event) {
		if (_event.type == sf::Event::MouseButtonPressed) {
			if (handleClickingUi(_event)) {
				return true;
			}
			if (handlePlacingBuilding(_event)) {
				return true;
			}
		}
		if (_event.type == sf::Event::KeyPressed) {
			if (_event.key.code == sf::Keyboard::Escape) {
				m_ActiveBuildingGhostIndex = -1;
				return true;
			}
			if (_event.key.code == sf::Keyboard::Num1) {
				if (m_BuildingDataUI.size() >= 0) {
					m_ActiveBuildingGhostIndex = 0;
					return true;
				}
			}
			if (_event.key.code == sf::Keyboard::Num2) {
				if (m_BuildingDataUI.size() >= 1) {
					m_ActiveBuildingGhostIndex = 1;
					return true;
				}
			}
			if (_event.key.code == sf::Keyboard::Num3) {
				if (m_BuildingDataUI.size() >= 2) {
					m_ActiveBuildingGhostIndex = 2;
					return true;
				}
			}
			if (_event.key.code == sf::Keyboard::Num4) {
				if (m_BuildingDataUI.size() >= 3) {
					m_ActiveBuildingGhostIndex = 3;
					return true;
				}
			}
			if (_event.key.code == sf::Keyboard::Num5) {
				if (m_BuildingDataUI.size() >= 4) {
					m_ActiveBuildingGhostIndex = 4;
					return true;
				}
			}
			if (_event.key.code == sf::Keyboard::Num6) {
				if (m_BuildingDataUI.size() >= 5) {
					m_ActiveBuildingGhostIndex = 5;
					return true;
				}
			}
			if (_event.key.code == sf::Keyboard::Num7) {
				if (m_BuildingDataUI.size() >= 6) {
					m_ActiveBuildingGhostIndex = 6;
					return true;
				}
			}
			if (_event.key.code == sf::Keyboard::Num8) {
				if (m_BuildingDataUI.size() >= 7) {
					m_ActiveBuildingGhostIndex = 7;
					return true;
				}
			}
			if (_event.key.code == sf::Keyboard::Num9) {
				if (m_BuildingDataUI.size() >= 8) {
					m_ActiveBuildingGhostIndex = 8;
					return true;
				}
			}
			if (_event.key.code == sf::Keyboard::Num0) {
				if (m_BuildingDataUI.size() >= 9) {
					m_ActiveBuildingGhostIndex = 9;
					return true;
				}
			}
		}
		return false;
	}
	void GameScene::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		const sf::Vector2f& Size = sf::Vector2f(_target.getSize());
		const float Scale = m_Config.getGameViewScale();
		const float SideAngleSize = 360.0f / m_WorldData.Sides;

		_states.transform.translate(Size / (2.0f * Scale));

		{
			sf::RenderStates worldStates(_states);
			worldStates.transform.rotate(m_WorldData.rotation);
			worldStates.transform.scale(1.0f / Scale, 1.0f / Scale);
			m_WorldObject.draw(_target, worldStates, _alpha);
		}

		{
			float i = 0;
			for (const BuildingObject& bo : m_BuildingObjects) {
				sf::RenderStates buildingStates(_states);
				buildingStates.transform.rotate(m_WorldData.rotation + SideAngleSize / 2.0f + SideAngleSize * i++);
				buildingStates.transform.translate(1.0f, 0.0f);
				buildingStates.transform.rotate(90.0f);
				buildingStates.transform.scale(1.0f / Scale, 1.0f / Scale);
				if (bo.getBuildingData().active) {
					bo.draw(_target, buildingStates, _alpha);
				}
			}
		}

		if (m_ActiveBuildingGhostIndex != -1) {
			const sf::Vector2f& mousePosition = sf::Vector2f(m_InputManager.getMousePositionRelativeToCenter()) / Scale;
			const float length = inf::VectorMath::length(mousePosition);
			const float angle = m_WorldInteractionService.getAngleRelativeToCenterOfScreen(mousePosition);
			const float sideIndex = static_cast<float>(m_WorldInteractionService.getWorldSegmentIndexForAngle(m_WorldData, angle));

			const float Radius = 0.05f;
			sf::CircleShape c(Radius);

			if (m_WorldInteractionService.getLengthWithinSnapMargin(m_WorldData, length)) {
				c.setPosition(inf::VectorMath::toDirection((sideIndex + 0.5f) * SideAngleSize + m_WorldData.rotation, inf::VectorMath::AngleType::Degrees));
				c.setFillColor(sf::Color::Cyan);
			} else {
				c.setPosition(mousePosition);
				c.setFillColor(sf::Color::Red);
			}
			c.setOrigin(Radius, Radius);
			_target.draw(c, _states);
		}

		{
			sf::RenderStates states{};
			const float HalfWidth = static_cast<float>(_target.getSize().x) / 2.0f;
			states.transform.translate(0.0f, 32.0f);
			const sf::View& originalView = _target.getView();
			_target.setView(_target.getDefaultView());
			_target.draw(m_GoldText, states);
			{
				sf::RenderStates resourceStates(states);
				resourceStates.transform.translate(0.0f, 32.0f);
				_target.draw(m_SpecialText, resourceStates);
			}
			states.transform.translate(HalfWidth, 0.0f);
			_target.draw(m_AgeText, states);
			states.transform.translate(HalfWidth - 256.0f, 0.0f);
			_target.draw(m_YearText, states);
			_target.setView(originalView);
		}

		{
			sf::RenderStates states{};
			const float Height = static_cast<float>(_target.getSize().y);
			const float Spacing = static_cast<float>(_target.getSize().x / m_BuildingTextThings.size() + 1);
			states.transform.translate(0.0f, Height - 32.0f);

			states.transform.translate(Spacing / 2.0f, 0.0f);
			for (unsigned i = 0; i < m_BuildingTextThings.size(); ++i) {
				sf::RenderStates uiItemState(states);
				
				const sf::Text& text = m_BuildingTextThings[i];
				_target.draw(text, uiItemState);

				uiItemState.transform.translate(0.0f, -32.0f);

				const BuildingObject& buildingObject = m_UIBuildingObjects[i];
				buildingObject.draw(_target, uiItemState, _alpha);

				states.transform.translate(Spacing, 0.0f);
			}
		}

	}

	void GameScene::initialise(const WorldDataInitialisationPackage& _worldInitialisationPackage) {
		m_WorldData.Sides = _worldInitialisationPackage.Sides;
		m_WorldData.SnapMargin = _worldInitialisationPackage.SnapMargin;

		m_WorldData.rotation = _worldInitialisationPackage.rotation;
		m_WorldData.rotationRate = _worldInitialisationPackage.rotationRate;

		m_WorldData.buildings.reserve(m_WorldData.Sides);

		for (int i = 0; i < m_WorldData.Sides; ++i) {
			m_WorldData.buildings.emplace_back();
			m_BuildingObjects.emplace_back(&m_WorldData.buildings[i], &m_AnimationPrototypes[0], m_TextureManager.getTexture(Definitions::BuildingTextureName));
		}
	}

	WorldObject& GameScene::getWorldObject(void) {
		return m_WorldObject;
	}

	bool GameScene::handleClickingUi(const sf::Event& _event) {
		const sf::Vector2f Size(m_InputManager.getWindowSize());
		const float Spacing = Size.x / static_cast<float>(m_BuildingTextThings.size());

		const sf::Vector2f StartingPlace(Spacing / 2.0f, Size.y - 32.0f);

		for (unsigned i = 0; i < m_BuildingTextThings.size(); ++i) {
			const sf::Vector2f CurrentCenter = StartingPlace + sf::Vector2f(Spacing * static_cast<float>(i), 0.0f);
			sf::FloatRect bounds(m_BuildingTextThings[i].getLocalBounds());
			bounds.width *= 2.0f;
			bounds.height *= 2.0f;
			bounds.left = CurrentCenter.x - bounds.width / 2.0f;
			bounds.top = CurrentCenter.y - bounds.height / 2.0f;

			if (bounds.contains(static_cast<float>(_event.mouseButton.x), static_cast<float>(_event.mouseButton.y))) {
				std::cout << "Text '" << m_BuildingTextThings[i].getString().toAnsiString() << "' contains mouse, lets start building " << m_BuildingDataUI[i].animationName << std::endl;
				m_ActiveBuildingGhostIndex = static_cast<int>(i);
				return true;
			} 
		}


		return false;
	}

	bool GameScene::handlePlacingBuilding(const sf::Event& _event) {
		if (m_ActiveBuildingGhostIndex == -1) {
			return false;
		}
		if (_event.type != sf::Event::MouseButtonPressed || _event.mouseButton.button != sf::Mouse::Left) {
			return false;
		}
		
		const sf::Vector2i& eventCoordinates = { _event.mouseButton.x , _event.mouseButton.y };
		const int segmentIndex = m_WorldInteractionService.getWorldSegmentForEventCoordinates(m_WorldData, eventCoordinates);

		BuildingData& prototype = m_BuildingDataUI[static_cast<unsigned>(m_ActiveBuildingGhostIndex)];
		const Definitions::PlaceBuildingResult& canPlace = m_WorldInteractionService.canPlacePrototypeatSegmentIndex(m_WorldData, prototype, segmentIndex);
		if (canPlace == Definitions::PlaceBuildingResult::InsufficientResources) {
			std::cout << "Cannot afford, costs" << std::endl;
			std::cout << prototype.cost.getResources();
			return false;
		}
		if (canPlace == Definitions::PlaceBuildingResult::CannotOverwrite) {
			std::cout << "Cannot overwrite equal/more advanced building" << std::endl;
			return false;
		}


		if (m_WorldInteractionService.getLengthWithinSnapMargin(m_WorldData, eventCoordinates)) {
			BuildingData newBuilding(prototype);
			newBuilding.active = true;
			m_WorldData.buildings[static_cast<unsigned>(segmentIndex)] = newBuilding;
			m_BuildingObjects[static_cast<unsigned>(segmentIndex)].reset(&m_WorldData.buildings[static_cast<unsigned>(segmentIndex)], &m_AnimationPrototypes[static_cast<unsigned>(m_ActiveBuildingGhostIndex)]);
			m_ResourceService.payResourceBundle(prototype.cost);

			const auto CurrentAge = m_ResourceService.getResource(Definitions::AgeResourceName);
			if (CurrentAge < prototype.age) {
				m_ResourceService.setResource(Definitions::AgeResourceName, std::min(CurrentAge + 1, prototype.age));
			}

			return true;
		}

		return false;
	}

}

