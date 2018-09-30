#ifndef INCLUDED_DRILLER_VIEWS_BUILDING_VIEW_HPP_
#define INCLUDED_DRILLER_VIEWS_BUILDING_VIEW_HPP_

#include <Driller/Views/View.hpp>
#include <Driller/DataStructures/BuildingData.hpp>
#include <Infrastructure/TextureManager.hpp>

namespace drl{

	class BuildingView : public View {
	public:
		BuildingView(inf::TextureManager& _textureManager, const BuildingData& _buildingData);
		~BuildingView(void) override;

		void update(float _delta) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

	protected:
		static void appendCell(sf::VertexArray& _vertex, const sf::Vector2u& _textureTileCoordinates, const sf::Vector2i& _tileCoordinates, const sf::Vector2u& _size);

	private:
		inf::TextureManager& m_TextureManager;
		const BuildingData& m_BuildingData;
	};

}

#endif // INCLUDED_DRILLER_VIEWS_BUILDING_VIEW_HPP_