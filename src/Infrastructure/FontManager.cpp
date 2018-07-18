#include <Infrastructure/FontManager.hpp>

#include <cassert>

namespace inf {
	FontManager::FontManager() {
	}

	FontManager::~FontManager() {
		for (auto p : m_Fonts) {
			delete p.second;
		}
	}

	bool FontManager::loadFont(const std::string& _filepath, const std::string& _fontName) {
		sf::Font *font = new sf::Font();

		if (font->loadFromFile(_filepath)) {
			m_Fonts.insert(std::make_pair(_fontName, font));
			return true;
		}
		delete font;
		return false;
	}
	sf::Font& FontManager::getFont(const std::string& _fontName) {
		auto iter = m_Fonts.find(_fontName);
		assert(iter != m_Fonts.end());

		return *(*iter).second;
	}
}