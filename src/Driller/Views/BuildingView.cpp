#include <Driller/Views/BuildingView.hpp>
#include <Driller/Infrastructure/Definitions.hpp>

namespace drl {

	BuildingView::BuildingView(inf::TextureManager& _textureManager, const BuildingData& _buildingData) :
		m_TextureManager(_textureManager),
		m_BuildingData(_buildingData) {
		
	}
	BuildingView::~BuildingView(void) {
		
	}

	void BuildingView::update(float _delta) {
		
	}
	void BuildingView::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		_states.texture = &m_TextureManager.getTexture(Definitions::TileSpriteSheetTextureName);
		sf::VertexArray vertex(sf::Triangles);

		for (const BuildingInstance& bi : m_BuildingData.buildings) {
			appendCell(vertex, sf::Vector2u(bi.textureCoords), bi.coordinates, bi.size);
		}


		_target.draw(vertex, _states);
	}

	void BuildingView::appendCell(sf::VertexArray& _vertex, const sf::Vector2u& _textureTileCoordinates, const sf::Vector2i& _tileCoordinates, const sf::Vector2u& _size) {
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
				static_cast<float>(_tileCoordinates.x + _size.x) - 0.5f,
				static_cast<float>(_tileCoordinates.y) + 0.0f) * Definitions::TileSize,
			sf::Vector2f(
				static_cast<float>(_textureTileCoordinates.x + _size.x),
				static_cast<float>(_textureTileCoordinates.y + 0)) * 64.0f)
		);
		_vertex.append(sf::Vertex(
			sf::Vector2f(
				static_cast<float>(_tileCoordinates.x + _size.x) - 0.5f,
				static_cast<float>(_tileCoordinates.y + _size.y)) * Definitions::TileSize,
			sf::Vector2f(
				static_cast<float>(_textureTileCoordinates.x + _size.x),
				static_cast<float>(_textureTileCoordinates.y + _size.y)) * 64.0f)
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
				static_cast<float>(_tileCoordinates.x + _size.x) - 0.5f,
				static_cast<float>(_tileCoordinates.y + _size.y)) * Definitions::TileSize,
			sf::Vector2f(
				static_cast<float>(_textureTileCoordinates.x + _size.x),
				static_cast<float>(_textureTileCoordinates.y + _size.y)) * 64.0f)
		);
		_vertex.append(sf::Vertex(
			sf::Vector2f(
				static_cast<float>(_tileCoordinates.x) - 0.5f,
				static_cast<float>(_tileCoordinates.y + _size.y)) * Definitions::TileSize,
			sf::Vector2f(
				static_cast<float>(_textureTileCoordinates.x + 0),
				static_cast<float>(_textureTileCoordinates.y + _size.y)) * 64.0f)
		);
	}

}
