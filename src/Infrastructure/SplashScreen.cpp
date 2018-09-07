#include <Infrastructure/SplashScreen.hpp>
#include <SFML/Graphics.hpp>

#define SPLASH_SCREEN_WIDTH 600
#define SPLASH_SCREEN_HEIGHT 300

#define LOADING_BAR_WIDTH 400
#define LOADING_BAR_HEIGHT 40
#define LOADING_BAR_MARGIN 4
#define PROGRESS_WIDTH LOADING_BAR_WIDTH - LOADING_BAR_MARGIN * 2
#define PROGRESS_HEIGHT LOADING_BAR_HEIGHT - LOADING_BAR_MARGIN * 2

namespace inf {

	SplashScreen::SplashScreen(const std::string& _texturePath, const std::string& _fontPath) {
		if (m_SplashScreenTexture.loadFromFile(_texturePath)) {
			m_SplashScreenSprite.setTexture(m_SplashScreenTexture);
		}
		if (m_SplashScreenFont.loadFromFile(_fontPath)) {
			m_SplashScreenText.setFont(m_SplashScreenFont);
			m_SplashScreenText.setOutlineThickness(2.0f);
			m_SplashScreenText.setOutlineColor(sf::Color::Black);
			m_SplashScreenText.setFillColor(sf::Color::White);

			m_LoadingPercentageText.setFont(m_SplashScreenFont);
			m_LoadingPercentageText.setOutlineThickness(2.0f);
			m_LoadingPercentageText.setOutlineColor(sf::Color::Black);
			m_LoadingPercentageText.setFillColor(sf::Color::White);
		}

		m_LoadingBarGraphic = sf::VertexArray(sf::Triangles, 3 * 2 * 3);
	}
	SplashScreen::~SplashScreen(void) {
		
	}

	void SplashScreen::show(void) {
		sf::RenderWindow window(sf::VideoMode(SPLASH_SCREEN_WIDTH, SPLASH_SCREEN_HEIGHT), "", sf::Style::None);
		
		m_Running = true;
		while (m_Running) {
			sf::Event event;
			while (window.pollEvent(event)) { }

			if (m_Mutex.try_lock()) {
				if (m_LoadingDataUpdated) {
					updateLoadingText(m_LoadingTextUpdate);
					updateLoadingPercentage(m_LoadingPercentageUpdate);
					m_LoadingDataUpdated = false;
				}
				m_Mutex.unlock();
			}

			window.draw(m_SplashScreenSprite);
			sf::RenderStates states{};
			states.transform.translate(SPLASH_SCREEN_WIDTH / 2.0f, SPLASH_SCREEN_HEIGHT - LOADING_BAR_HEIGHT * 2.0f);
			window.draw(m_LoadingBarGraphic, states);
			window.draw(m_LoadingPercentageText, states);
			states.transform.translate(0.0f, LOADING_BAR_HEIGHT);
			window.draw(m_SplashScreenText, states);
			window.display();
		}
	}


	void SplashScreen::close(void) {
		m_Running = false;
	}

	void SplashScreen::setLoadingState(unsigned _percentage, const std::string& _text) {
		m_Mutex.lock();
		m_LoadingDataUpdated = true;
		m_LoadingPercentageUpdate = unsigned(_percentage);
		m_LoadingTextUpdate = std::string(_text);
		m_Mutex.unlock();
	}

	void SplashScreen::updateLoadingText(const std::string& _loadingText) {
		m_SplashScreenText.setString(_loadingText);
		const sf::FloatRect textRect = m_SplashScreenText.getLocalBounds();
		m_SplashScreenText.setOrigin(
			textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f
		);		
	}
	void SplashScreen::updateLoadingPercentage(unsigned _percentage) {
		m_LoadingPercentageValue = _percentage;
		m_LoadingPercentageText.setString(std::to_string(_percentage) + "%");
		const sf::FloatRect textRect = m_LoadingPercentageText.getLocalBounds();
		m_LoadingPercentageText.setOrigin(
			textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f
		);
		updateLoadingBarGraphic(_percentage);
	}

	void SplashScreen::updateLoadingBarGraphic(unsigned _percentage) {
		
		{
			// Outline
			m_LoadingBarGraphic[0]  = sf::Vertex(sf::Vector2f(-LOADING_BAR_WIDTH / 2.0f, -LOADING_BAR_HEIGHT / 2.0f), sf::Color::White);
			m_LoadingBarGraphic[1]  = sf::Vertex(sf::Vector2f(+LOADING_BAR_WIDTH / 2.0f, -LOADING_BAR_HEIGHT / 2.0f), sf::Color::White);
			m_LoadingBarGraphic[2]  = sf::Vertex(sf::Vector2f(+LOADING_BAR_WIDTH / 2.0f, +LOADING_BAR_HEIGHT / 2.0f), sf::Color::White);

			m_LoadingBarGraphic[3]  = sf::Vertex(sf::Vector2f(-LOADING_BAR_WIDTH / 2.0f, -LOADING_BAR_HEIGHT / 2.0f), sf::Color::White);
			m_LoadingBarGraphic[4]  = sf::Vertex(sf::Vector2f(+LOADING_BAR_WIDTH / 2.0f, +LOADING_BAR_HEIGHT / 2.0f), sf::Color::White);
			m_LoadingBarGraphic[5]  = sf::Vertex(sf::Vector2f(-LOADING_BAR_WIDTH / 2.0f, +LOADING_BAR_HEIGHT / 2.0f), sf::Color::White);
		}
		{
			// Background
			m_LoadingBarGraphic[6]  = sf::Vertex(sf::Vector2f(-LOADING_BAR_WIDTH / 2.0f + LOADING_BAR_MARGIN, -LOADING_BAR_HEIGHT / 2.0f + LOADING_BAR_MARGIN), sf::Color(65, 65, 65));
			m_LoadingBarGraphic[7]  = sf::Vertex(sf::Vector2f(+LOADING_BAR_WIDTH / 2.0f - LOADING_BAR_MARGIN, -LOADING_BAR_HEIGHT / 2.0f + LOADING_BAR_MARGIN), sf::Color(65, 65, 65));
			m_LoadingBarGraphic[8]  = sf::Vertex(sf::Vector2f(+LOADING_BAR_WIDTH / 2.0f - LOADING_BAR_MARGIN, +LOADING_BAR_HEIGHT / 2.0f - LOADING_BAR_MARGIN), sf::Color(65, 65, 65));

			m_LoadingBarGraphic[9]  = sf::Vertex(sf::Vector2f(-LOADING_BAR_WIDTH / 2.0f + LOADING_BAR_MARGIN, -LOADING_BAR_HEIGHT / 2.0f + LOADING_BAR_MARGIN), sf::Color(65, 65, 65));
			m_LoadingBarGraphic[10] = sf::Vertex(sf::Vector2f(+LOADING_BAR_WIDTH / 2.0f - LOADING_BAR_MARGIN, +LOADING_BAR_HEIGHT / 2.0f - LOADING_BAR_MARGIN), sf::Color(65, 65, 65));
			m_LoadingBarGraphic[11] = sf::Vertex(sf::Vector2f(-LOADING_BAR_WIDTH / 2.0f + LOADING_BAR_MARGIN, +LOADING_BAR_HEIGHT / 2.0f - LOADING_BAR_MARGIN), sf::Color(65, 65, 65));
		}
		{
			// Progress

			const unsigned progressWidth = static_cast<unsigned>(static_cast<float>(PROGRESS_WIDTH) * static_cast<float>(m_LoadingPercentageValue) / 100.0f);

			m_LoadingBarGraphic[12] = sf::Vertex(m_LoadingBarGraphic[6].position + sf::Vector2f(), sf::Color::Green);
			m_LoadingBarGraphic[13] = sf::Vertex(m_LoadingBarGraphic[6].position + sf::Vector2f(progressWidth, 0.0f), sf::Color::Green);
			m_LoadingBarGraphic[14] = sf::Vertex(m_LoadingBarGraphic[6].position + sf::Vector2f(progressWidth, PROGRESS_HEIGHT), sf::Color::Green);

			m_LoadingBarGraphic[15] = sf::Vertex(m_LoadingBarGraphic[6].position + sf::Vector2f(), sf::Color::Green);
			m_LoadingBarGraphic[16] = sf::Vertex(m_LoadingBarGraphic[6].position + sf::Vector2f(progressWidth, PROGRESS_HEIGHT), sf::Color::Green);
			m_LoadingBarGraphic[17] = sf::Vertex(m_LoadingBarGraphic[6].position + sf::Vector2f(0.0f, PROGRESS_HEIGHT), sf::Color::Green);
		}
	}

}
