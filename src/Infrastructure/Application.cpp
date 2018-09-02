#include <Infrastructure/Application.hpp>
#include <iostream>

namespace inf {

	Application::Application(FontManager& _fontManager, SceneManager& _sceneManager) :
		m_Running(false),
		m_IsInitialised(false),
		m_FontManager(_fontManager),
		m_SceneManager(_sceneManager) {
		
	}

	Application::~Application(void) {
	}


	sf::Vector2f Application::convertEventCoordsToGameCoords(const sf::Vector2i& _coords) const {
		return m_Window.mapPixelToCoords(_coords, m_GameView);
	}
	sf::View& Application::getGameView(void) {
		return m_GameView;
	}

	void Application::initialise(const sf::Vector2u& _resolution, const std::string& _title, float _scale) {
		m_IsInitialised = true;

		srand(static_cast<unsigned int>(time(nullptr)));

		m_Window.create(sf::VideoMode(_resolution.x, _resolution.y), _title, sf::Style::Close | sf::Style::Titlebar);
		m_Window.setVerticalSyncEnabled(false);
		m_Window.setKeyRepeatEnabled(false);

		const sf::Vector2f size = sf::Vector2f(m_Window.getSize()) / _scale;

		m_GameView = sf::View(size / 2.0f, size);
		m_UiView = sf::View(sf::Vector2f(m_Window.getSize()) / 2.0f, sf::Vector2f(m_Window.getSize()));

#ifdef _DEBUG
#ifdef GAMES_WIN32
		m_FontManager.loadFont("C:/Windows/Fonts/arial.ttf", "DEBUG");
#endif
#endif

	}

	void Application::start(void) {
		if (!m_IsInitialised) {
			std::cerr << "Must initialise application before starting" << std::endl;
			return;
		}

#ifdef _DEBUG
#ifdef GAMES_WIN32
		m_FPSText.setCharacterSize(16);
		m_FPSText.setFont(m_FontManager.getFont("DEBUG"));
		m_FPSText.setFillColor(sf::Color::White);
		m_FPSText.setOutlineColor(sf::Color::Black);
		m_FPSText.setOutlineThickness(2.0f);
		m_FPSText.setString("FPS: 60, UPS: 60");
#endif
#endif

		m_Running = true;

		sf::Clock clock;
		const float delta = 1.0f / 60.0f;
		float accumulator = 0.0f;
		float statsAccumulator = 0.0f;
		unsigned int fps = 0;
		unsigned int ups = 0;

		while (m_Running) {
			float frameTime = clock.restart().asSeconds();
			if (frameTime > 0.5f) {
				frameTime = 0.5f;
			}

			accumulator += frameTime;

#ifdef _DEBUG
#ifdef GAMES_WIN32
			statsAccumulator += frameTime;

			if (statsAccumulator >= 1.0f) {
				m_FPSText.setString("FPS: " + std::to_string(fps) + ", UPS: " + std::to_string(ups));
				statsAccumulator -= 1.0f;
				fps = 0;
				ups = 0;
			}
#endif
#endif
			while (accumulator >= delta) {
				// Handle events
				sf::Event event;
				while (m_Window.pollEvent(event)) {
					handleEvent(event);
				}

				// Update
				update(delta);
				ups++;
				
				accumulator -= delta;
			}

			// Render
			render(accumulator / delta);
			fps++;
		}

		m_Window.close();
	}

	void Application::update(float _delta) const {
		m_SceneManager.update(_delta);
	}

	void Application::handleEvent(const sf::Event& _event) {
		if (m_SceneManager.handleEvent(_event)) {
			return;
		}
		if (_event.type == sf::Event::Closed) {
			m_Running = false;
		}
	}

	void Application::render(float _alpha) {
		m_Window.clear(sf::Color::Black);
		
		m_Window.setView(m_GameView);

		m_SceneManager.draw(m_Window, sf::RenderStates::Default, _alpha);

		m_Window.setView(m_UiView);

#ifdef _DEBUG
#ifdef GAMES_WIN32
		m_Window.draw(m_FPSText, sf::RenderStates::Default);
#endif
#endif

		m_Window.display();
	}
}
