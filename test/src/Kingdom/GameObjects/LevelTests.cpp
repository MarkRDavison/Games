#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Kingdom/GameObjects/Level.hpp>

namespace kdm {
	namespace LevelTests {
		TEST_CASE("Initialising level sets width and height correctly", "[GameObject][Level]") {
			const unsigned w = 2;
			const unsigned h = 5;
			ParsedLevel pl{};
			pl.width = w;
			pl.height = h;
			kdm::Level l;
			l.initialize(pl);

			REQUIRE(w == l.getWidth());
			REQUIRE(h == l.getHeight());
		}
	}
}