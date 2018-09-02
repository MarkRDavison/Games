#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>

#include <Infrastructure/LuaConsole.hpp>
#include <Mocks/Infrastructure/LuaManagerMock.hpp>

namespace inf {
	namespace LuaConsoleTests {
		TEST_CASE("Toggling the console updates whether it is open", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);

			REQUIRE_FALSE(console.isOpen());

			console.toggle();

			REQUIRE(console.isOpen());

			console.toggle();

			REQUIRE_FALSE(console.isOpen());

			console.toggle();

			REQUIRE(console.isOpen());
		}

		TEST_CASE("Setting the console to open/closed updates whether it is open", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);

			REQUIRE_FALSE(console.isOpen());

			console.setOpen();

			REQUIRE(console.isOpen());

			console.setClosed();

			REQUIRE_FALSE(console.isOpen());
		}

		TEST_CASE("Console doesnt handle an event when closed", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);

			sf::Event e{};
			e.type = sf::Event::TextEntered;
			e.text.unicode = 'A';

			REQUIRE_FALSE(console.isOpen());
			REQUIRE_FALSE(console.handleEvent(e));
		}

		TEST_CASE("Console handles a text entered event when open", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);
			console.setOpen();

			sf::Event e{};
			e.type = sf::Event::TextEntered;
			e.text.unicode = 'A';
			
			REQUIRE(console.handleEvent(e));
		}

		TEST_CASE("Open console handling text entered event for basic character appends it to current text", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);
			console.setOpen();

			sf::Event e{};
			e.type = sf::Event::TextEntered;
			e.text.unicode = 'A';

			REQUIRE(console.handleEvent(e));
			REQUIRE("A" == console.getCurrentText());
			e.text.unicode = 'B';
			REQUIRE(console.handleEvent(e));
			REQUIRE("AB" == console.getCurrentText());
			e.text.unicode = 'C';
			REQUIRE(console.handleEvent(e));
			REQUIRE("ABC" == console.getCurrentText());
		}

		TEST_CASE("Open console will handle an enter key pressed event", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);
			console.setOpen();

			sf::Event e{};
			e.type = sf::Event::KeyPressed;
			e.key.code = sf::Keyboard::Key::Return;

			REQUIRE(console.handleEvent(e));
		}
		
		TEST_CASE("Open console will handle a backspace key pressed event on an empty current text", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);
			console.setOpen();

			sf::Event e{};
			e.type = sf::Event::KeyPressed;
			e.key.code = sf::Keyboard::Key::BackSpace;

			REQUIRE(console.handleEvent(e));
		}
		
		TEST_CASE("Open console will handle a backspace key pressed event on a current text and reduce it", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);
			console.setOpen();

			sf::Event e{};

			e.type = sf::Event::TextEntered;
			e.text.unicode = 'A'; 			
			console.handleEvent(e);
			REQUIRE("A" == console.getCurrentText());

			e.type = sf::Event::KeyPressed;
			e.key.code = sf::Keyboard::Key::BackSpace;
			console.handleEvent(e);
			REQUIRE("" == console.getCurrentText());
		}
		
		TEST_CASE("Open console will handle a ctrl+backspace key pressed event on a current text and reduce it to the next space", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);
			console.setOpen();

			sf::Event e{};

			e.type = sf::Event::TextEntered;
			e.text.unicode = 'A';
			console.handleEvent(e);
			console.handleEvent(e);
			console.handleEvent(e);
			e.text.unicode = ' ';
			console.handleEvent(e);
			console.handleEvent(e);
			e.text.unicode = 'A';
			console.handleEvent(e);
			console.handleEvent(e);
			REQUIRE("AAA  AA" == console.getCurrentText());

			e.type = sf::Event::KeyPressed;
			e.key.code = sf::Keyboard::Key::BackSpace;
			e.key.control = true;
			console.handleEvent(e);
			REQUIRE("AAA" == console.getCurrentText());
		}
		
		TEST_CASE("Open console will handle an enter key pressed event and clear the current text", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);
			console.setOpen();

			sf::Event e{};

			e.type = sf::Event::TextEntered;
			e.text.unicode = 'A';
			console.handleEvent(e);
			REQUIRE("A" == console.getCurrentText());

			e.type = sf::Event::KeyPressed;
			e.key.code = sf::Keyboard::Key::Return;
			REQUIRE(console.handleEvent(e));
			REQUIRE(console.getCurrentText().empty());
		}
		
		TEST_CASE("Open console will handle an enter key pressed event and put the current text into the past command buffer", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);
			console.setOpen();

			REQUIRE(inf::LuaConsole::PreviousCommandBufferMaxSize == console.getPreviousCommandBuffer().size());
			REQUIRE(0 == console.getCurrentCommandBufferIndex());

			sf::Event e{};

			e.type = sf::Event::TextEntered;
			e.text.unicode = 'A';
			console.handleEvent(e);
			e.type = sf::Event::KeyPressed;
			e.key.code = sf::Keyboard::Key::Return;
			console.handleEvent(e);

			REQUIRE(console.getCurrentText().empty());
			REQUIRE(1 == console.getCurrentCommandBufferIndex());
			REQUIRE("A" == console.getPreviousCommandBuffer()[0]);
		}

		TEST_CASE("Pressing enter on an open console closes it", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);
			console.setOpen();

			sf::Event e{};

			e.type = sf::Event::TextEntered;
			e.text.unicode = 'A';
			console.handleEvent(e);

			e.type = sf::Event::KeyPressed;
			e.key.code = sf::Keyboard::Key::Return;
			console.handleEvent(e);

			REQUIRE_FALSE(console.isOpen());
		}

		TEST_CASE("Pressing escape on an open console closes it", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);
			console.setOpen();

			sf::Event e{};
			e.type = sf::Event::KeyPressed;
			e.key.code = sf::Keyboard::Key::Escape;
			console.handleEvent(e);

			REQUIRE_FALSE(console.isOpen());
		}

		TEST_CASE("The backspace key text entered event does not get added to the current text", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);
			console.setOpen(true);

			sf::Event e{};
			e.type = sf::Event::TextEntered;
			e.text.unicode = 8;
			console.handleEvent(e);

			REQUIRE(console.getCurrentText().empty());
		}

		TEST_CASE("The tilde key text entered event does not get added to the current text when suppressed", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);
			console.setOpen(true);

			sf::Event e{};
			e.type = sf::Event::TextEntered;
			e.text.unicode = '~';
			console.handleEvent(e);

			REQUIRE(console.getCurrentText().empty());
		}

		TEST_CASE("The tilde key text entered event gets added to the current text when not suppressed", "[LuaConsole]") {
			inf::LuaManagerMock luaManager;
			inf::LuaConsole console("", luaManager);
			console.setOpen(false);

			sf::Event e{};
			e.type = sf::Event::TextEntered;
			e.text.unicode = '~';
			console.handleEvent(e);

			REQUIRE("~" == console.getCurrentText());
		}
	}
}