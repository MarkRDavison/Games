#ifndef INCLUDED_INFRASTRUCTURE_SPLASH_SCREEN_HPP_
#define INCLUDED_INFRASTRUCTURE_SPLASH_SCREEN_HPP_

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <mutex>

namespace inf {

	class SplashScreen {
	public:
		SplashScreen(const std::string& _texturePath, const std::string& _fontPath);
		~SplashScreen(void);

		void show(void);
		void close(void);
		void setLoadingState(unsigned _percentage, const std::string& _text);


	private:
		void updateLoadingBarGraphic(unsigned _percentage);

		void updateLoadingText(const std::string& _loadingText);
		void updateLoadingPercentage(unsigned _percentage);

	private:
		sf::Texture m_SplashScreenTexture;
		sf::Sprite m_SplashScreenSprite;
		sf::Font m_SplashScreenFont;
		sf::Text m_SplashScreenText;
		sf::Text m_LoadingPercentageText;
		sf::VertexArray m_LoadingBarGraphic;
		unsigned m_LoadingPercentageValue{ 0 };

		std::mutex m_Mutex;
		bool m_LoadingDataUpdated{false};
		std::string m_LoadingTextUpdate;
		unsigned m_LoadingPercentageUpdate{0};

		bool m_Running{ false };
	};
	
}

#endif // INCLUDED_INFRASTRUCTURE_SPLASH_SCREEN_HPP_