#ifndef INCLUDED_DRILLER_VIEWS_TERRAIN_VIEW_HPP_
#define INCLUDED_DRILLER_VIEWS_TERRAIN_VIEW_HPP_

#include <Driller/Views/View.hpp>
#include <Driller/DataStructures/TerrainData.hpp>
#include <Infrastructure/TextureManager.hpp>

namespace drl {
	
	class TerrainView : public View {
	public:
		TerrainView(inf::TextureManager& _textureManager, const TerrainData& _terrainData);
		~TerrainView(void) override;

		void update(float _delta) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

	protected:
		static void appendCell(sf::VertexArray& _vertex, const sf::Vector2u& _textureTileCoordinates, const sf::Vector2i& _tileCoordinates);

	private:
		inf::TextureManager& m_TextureManager;
		const TerrainData& m_TerrainData;
	};

}

#endif // INCLUDED_DRILLER_VIEWS_TERRAIN_VIEW_HPP_