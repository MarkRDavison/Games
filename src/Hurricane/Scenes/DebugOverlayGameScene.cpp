#include <Hurricane/Scenes/DebugOverlayGameScene.hpp>
#include <Hurricane/Infrastructure/EntityGroups.hpp>

namespace hur {

	DebugOverlayGameScene::DebugOverlayGameScene(ecs::EntityManager& _entityManager, inf::FontManager& _fontManager) :
		inf::Scene("hur::DebugOverlayGameScene"),
		m_EntityManager(_entityManager),
		m_NumberOfEntitiesText("Entities: ~", _fontManager.getFont("DEBUG"), 16u),
		m_NumberOfProjectilesText("Projectiles: ~", _fontManager.getFont("DEBUG"), 16u) {

		m_NumberOfEntitiesText.setFillColor(sf::Color::White);
		m_NumberOfEntitiesText.setOutlineColor(sf::Color::Black);
		m_NumberOfEntitiesText.setOutlineThickness(2.0f);

		m_NumberOfProjectilesText.setFillColor(sf::Color::White);
		m_NumberOfProjectilesText.setOutlineColor(sf::Color::Black);
		m_NumberOfProjectilesText.setOutlineThickness(2.0f);
		
	}
	DebugOverlayGameScene::~DebugOverlayGameScene(void) {
		
	}

	void DebugOverlayGameScene::update(float _delta) {
		updateAccumulation += _delta;
		if (updateAccumulation >= updateRate) {
			updateAccumulation -= updateRate;
			m_NumberOfEntitiesText.setString("Entities: " + std::to_string(m_EntityManager.getNumberOfEntities()));
			m_NumberOfProjectilesText.setString("Projectiles: " + std::to_string(m_EntityManager.getEntitiesByGroup(hurr::EntityGroup::GProjectile).size()));
		}
	}
	bool DebugOverlayGameScene::handleEvent(const sf::Event& _event) {
		return false;
	}
	void DebugOverlayGameScene::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
		const sf::View originalView = _target.getView();

		_target.setView(_target.getDefaultView());

		sf::RenderStates states{};

		states.transform.translate(0.0f, 16.0f);
		_target.draw(m_NumberOfEntitiesText, states);

		states.transform.translate(0.0f, 16.0f);
		_target.draw(m_NumberOfProjectilesText, states);

		_target.setView(originalView);
	}

}
