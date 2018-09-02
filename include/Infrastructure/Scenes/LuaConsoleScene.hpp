#ifndef INCLUDED_INFRASTRUCTURE_SCENES_LUA_CONSOLE_SCENE_HPP_
#define INCLUDED_INFRASTRUCTURE_SCENES_LUA_CONSOLE_SCENE_HPP_

#include <Infrastructure/Scene.hpp>
#include <Infrastructure/LuaConsole.hpp>
#include <Infrastructure/FontManager.hpp>

namespace inf {
	class LuaConsoleScene : public Scene {
	public:
		LuaConsoleScene(LuaConsole& _luaConsole, FontManager& _fontManager);
		~LuaConsoleScene(void);

		void update(float _delta) override;
		bool handleEvent(const sf::Event& _event) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

	private:
		LuaConsole& m_LuaConsole;
		FontManager& m_FontManager;
	};
}

#endif // INCLUDED_INFRASTRUCTURE_SCENES_LUA_CONSOLE_SCENE_HPP_