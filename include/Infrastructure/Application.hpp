#ifndef INCLUDED_EXPEDITION_INFRASTRUCTURE_APPLICATION_HPP_
#define INCLUDED_EXPEDITION_INFRASTRUCTURE_APPLICATION_HPP_

#include <SFML/Graphics.hpp>
#include <Infrastructure/FontManager.hpp>
#include <Infrastructure/SceneManager.hpp>

namespace inf {
	class Application {
	public:
		Application(FontManager& _fontManager, SceneManager& _sceneManager);
		~Application(void);

		sf::Vector2f convertEventCoordsToGameCoords(const sf::Vector2i& _coords) const;
		sf::View& getGameView(void);

		void initialise(const sf::Vector2u& _resolution, const std::string& _title, float _scale);
		void start(void);

		sf::RenderTarget& getRenderTarget(void) noexcept { return m_Window; }
		const sf::Window& getWindow(void) noexcept { return m_Window; }

	private:

		void update(float _delta) const;
		void handleEvent(const sf::Event& _event);
		void render(float _alpha);

	private:
		bool m_Running;
		bool m_IsInitialised;

		sf::RenderWindow m_Window;
		sf::View m_GameView;
		sf::View m_UiView;

#ifdef _DEBUG
		sf::Text m_FPSText;
#endif

		FontManager& m_FontManager;
		SceneManager& m_SceneManager;
	};
}

#endif // INCLUDED_EXPEDITION_INFRASTRUCTURE_APPLICATION_HPP_