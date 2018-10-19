#ifndef INCLUDED_SOVEREIGN_CORE_DEFINITIONS_HPP_
#define INCLUDED_SOVEREIGN_CORE_DEFINITIONS_HPP_

namespace sov {

	class Definitions {
		Definitions(void) = delete;
		~Definitions(void) = delete;
	public:

		static constexpr const float TileSize{ 1.0f };
		static constexpr const float Epsilon{ 0.00001f };
		static constexpr const unsigned ChunkSize{ 12 };

		static constexpr const char MoneyResourceName[] = "Money";

		static constexpr const char DefaultFontName[] = "FontName";

		static constexpr const char TerrainTextureName[] = "Terrain";

		enum class GameSceneState {
			Title,
			Gameplay,
			Exit,

			Invalid
		};

	};

}

#endif // INCLUDED_SOVEREIGN_CORE_DEFINITIONS_HPP_