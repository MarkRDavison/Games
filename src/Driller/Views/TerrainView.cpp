#include <Driller/Views/TerrainView.hpp>
#include <Driller/Infrastructure/Definitions.hpp>

namespace drl {

	TerrainView::TerrainView(inf::TextureManager& _textureManager, const TerrainData& _terrainData) :
		m_TextureManager(_textureManager),
		m_TerrainData(_terrainData) {
		
	}
	TerrainView::~TerrainView(void) {
		
	}

	void TerrainView::update(float _delta) {
		
	}
	void TerrainView::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		const float TSize{ 64.0f };
		const sf::Vector2u DefaultTerrain{ 0, 0 };
		const sf::Vector2u DugOutTerrain{ 1, 0 };
		const sf::Vector2u LadderTerrain{ 0, 1 };
		const sf::Vector2u DrillTerrain{ 0, 2 };

		_states.texture = &m_TextureManager.getTexture(Definitions::TileSpriteSheetTextureName);

		sf::VertexArray terrainLeft(sf::Triangles);
		sf::VertexArray terrainCenter(sf::Triangles);
		sf::VertexArray terrainRight(sf::Triangles);
		{
			for (int i = 0; i < static_cast<int>(m_TerrainData.rows.size()); ++i) {
				const TerrainRow& row = m_TerrainData.rows[i];

				appendCell(terrainCenter, LadderTerrain, { 0, i });

				for (int j = 1; j <= static_cast<int>(row.leftTiles.size()); ++j) {
					appendCell(terrainLeft, row.leftTiles[j - 1].dugOut ? DugOutTerrain : DefaultTerrain, { -j, i });
				}

				for (int k = 1; k <= static_cast<int>(row.rightTiles.size()); ++k) {
					appendCell(terrainLeft, row.rightTiles[k - 1].dugOut ? DugOutTerrain : DefaultTerrain, { +k, i });
				}
			}
			appendCell(terrainCenter, DrillTerrain, sf::Vector2i(0, static_cast<int>(m_TerrainData.rows.size())));
		}

		_target.draw(terrainLeft, _states);
		_target.draw(terrainCenter, _states);
		_target.draw(terrainRight, _states);
	}

	void TerrainView::appendCell(sf::VertexArray& _vertex, const sf::Vector2u& _textureTileCoordinates, const sf::Vector2i& _tileCoordinates) {
		_vertex.append(sf::Vertex(
			sf::Vector2f(
				static_cast<float>(_tileCoordinates.x) - 0.5f,
				static_cast<float>(_tileCoordinates.y) + 0.0f) * Definitions::TileSize,
			sf::Vector2f(
				static_cast<float>(_textureTileCoordinates.x + 0),
				static_cast<float>(_textureTileCoordinates.y + 0)) * 64.0f)
		);
		_vertex.append(sf::Vertex(
			sf::Vector2f(
				static_cast<float>(_tileCoordinates.x) + 0.5f,
				static_cast<float>(_tileCoordinates.y) + 0.0f) * Definitions::TileSize,
			sf::Vector2f(
				static_cast<float>(_textureTileCoordinates.x + 1),
				static_cast<float>(_textureTileCoordinates.y + 0)) * 64.0f)
		);
		_vertex.append(sf::Vertex(
			sf::Vector2f(
				static_cast<float>(_tileCoordinates.x) + 0.5f,
				static_cast<float>(_tileCoordinates.y) + 1.0f) * Definitions::TileSize,
			sf::Vector2f(
				static_cast<float>(_textureTileCoordinates.x + 1),
				static_cast<float>(_textureTileCoordinates.y + 1)) * 64.0f)
		);

		_vertex.append(sf::Vertex(
			sf::Vector2f(
				static_cast<float>(_tileCoordinates.x) - 0.5f,
				static_cast<float>(_tileCoordinates.y) + 0.0f) * Definitions::TileSize,
			sf::Vector2f(
				static_cast<float>(_textureTileCoordinates.x + 0),
				static_cast<float>(_textureTileCoordinates.y + 0)) * 64.0f)
		);
		_vertex.append(sf::Vertex(
			sf::Vector2f(
				static_cast<float>(_tileCoordinates.x) + 0.5f,
				static_cast<float>(_tileCoordinates.y) + 1.0f) * Definitions::TileSize,
			sf::Vector2f(
				static_cast<float>(_textureTileCoordinates.x + 1),
				static_cast<float>(_textureTileCoordinates.y + 1)) * 64.0f)
		);
		_vertex.append(sf::Vertex(
			sf::Vector2f(
				static_cast<float>(_tileCoordinates.x) - 0.5f,
				static_cast<float>(_tileCoordinates.y) + 1.0f) * Definitions::TileSize,
			sf::Vector2f(
				static_cast<float>(_textureTileCoordinates.x + 0),
				static_cast<float>(_textureTileCoordinates.y + 1)) * 64.0f)
		);
	}

}
