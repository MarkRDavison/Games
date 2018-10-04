#include <Driller/Services/TerrainAlterationService.hpp>
#include <cassert>
#include <cmath>

namespace drl {

	TerrainAlterationService::TerrainAlterationService(TerrainData& _terrainData) :
		m_TerrainData(_terrainData) {
		
	}

	TerrainAlterationService::~TerrainAlterationService(void) {
		
	}

	bool TerrainAlterationService::digShaft(int _level) {
		if (static_cast<int>(m_TerrainData.rows.size()) == _level) {
			m_TerrainData.rows.emplace_back();
			return true;
		}

		return false;
	}

	bool TerrainAlterationService::digTile(int _level, int _x) {
		if (_x == 0) {
			return false;
		}

		if (static_cast<int>(m_TerrainData.rows.size()) > _level) {
			TerrainRow& row = m_TerrainData.rows[static_cast<unsigned>(_level)];
			const unsigned xCoord = static_cast<unsigned>(std::abs(_x)) - (_x == 0 ? 0 : 1);
			if (_x > 0) {
				if (row.rightTiles.size() == xCoord) {
					// Need to append a new tile
					TerrainTile& t = row.rightTiles.emplace_back();
					t.jobReserved = false;
					t.dugOut = true;
					return true;
				}
				if (row.rightTiles.size() > xCoord) {
					// There is already a tile, just need to dig it out
					TerrainTile& t = row.rightTiles[xCoord];
					if (t.dugOut) {
						return false;
					}
					t.jobReserved = false;
					t.dugOut = true;
					return true;
				}

				return false;
			}

			if (_x < 0) {
				if (row.leftTiles.size() == xCoord) {
					// Need to append a new tile
					TerrainTile& t = row.leftTiles.emplace_back();
					t.jobReserved = false;
					t.dugOut = true;
					return true;
				}
				if (row.leftTiles.size() > xCoord) {
					// There is already a tile, just need to dig it out
					TerrainTile& t = row.leftTiles[xCoord];
					if (t.dugOut) {
						return false;
					}
					t.jobReserved = false;
					t.dugOut = true;
					return true;
				}

				return false;
			}
		}

		return false;
	}

	void TerrainAlterationService::initialiseTile(int _level, int _column) {
		if (doesTileExist(_level, _column)) {
			return;
		}

		while (static_cast<int>(m_TerrainData.rows.size()) <= _level) {
			m_TerrainData.rows.emplace_back();
		}

		TerrainRow& row = m_TerrainData.rows[_level];
		const int xCoord = std::abs(_column) - 1;

		if (_column > 0) {
			while (static_cast<int>(row.rightTiles.size()) <= xCoord) {
				row.rightTiles.emplace_back();
			}
		}

		if (_column < 0) {
			while (static_cast<int>(row.leftTiles.size()) <= xCoord) {
				row.leftTiles.emplace_back();
			}
		}
	}

	bool TerrainAlterationService::doesTileExist(int _level, int _column) const {
		return m_TerrainData.tileExists(_level, _column);
	}

	bool TerrainAlterationService::doesLevelExist(int _level) const {
		return static_cast<int>(m_TerrainData.rows.size()) > _level;
	}

	bool TerrainAlterationService::isTileDugOut(int _level, int _column) const {
		if (doesTileExist(_level, _column)) {
			return m_TerrainData.getTile(_level, _column).dugOut;
		}
		return false;
	}

	void TerrainAlterationService::reserveJobOnTile(int _level, int _column) {
		assert(doesTileExist(_level, _column));

		m_TerrainData.getTile(_level, _column).jobReserved = true;
	}

	const TerrainTile& TerrainAlterationService::getTile(int _level, int _column) const {
		assert(doesTileExist(_level, _column));

		return m_TerrainData.getTile(_level, _column);
	}

}
