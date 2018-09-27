#include <Infrastructure/TextureManager.hpp>

#include <cassert>

namespace inf {

	TextureManager::TextureManager() {
	}

	TextureManager::~TextureManager() {
		for (auto p : m_Textures) {
			delete p.second;
		}
	}


	bool TextureManager::loadTexture(const std::string& _filepath, const std::string& _textureName) {
		sf::Texture *texture = new sf::Texture();

		if (texture->loadFromFile(_filepath)) {
			m_Textures.insert(std::make_pair(_textureName, texture));
			texture->setSmooth(true);
			texture->generateMipmap();
			return true;
		}
		delete texture;
		return false;
	}

	sf::Texture& TextureManager::getTexture(const std::string& _textureName) {
		auto iter = m_Textures.find(_textureName);
		assert(iter != m_Textures.end());

		return *(*iter).second;
	}
}