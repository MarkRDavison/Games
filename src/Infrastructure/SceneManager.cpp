#include <Infrastructure/SceneManager.hpp>

namespace inf {
	SceneManager::SceneManager() {
	}
	
	SceneManager::~SceneManager() {
		for (auto scene : m_Scenes) {
			delete scene;
		}
	}

	void SceneManager::update(float _delta) {
		for (auto& scene : m_Scenes) {
			scene->update(_delta);
		}
	}
	bool SceneManager::handleEvent(const sf::Event& _event) {
		// TODO: Make this traverse backwards?
		for (auto& scene : m_Scenes) {
			if (scene->handleEvent(_event)) {
				return true;
			}
		}
		return false;
	}

	void SceneManager::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
		for (const auto& scene : m_Scenes) {
			scene->draw(_target, _states);
		}
	}

	void SceneManager::pushScene(Scene *_scene) {
		m_Scenes.push_back(_scene);
	}
	Scene *SceneManager::popScene(void) {
		const auto popped = m_Scenes.back();
		m_Scenes.erase(m_Scenes.begin() + m_Scenes.size() - 1);
		return popped;
	}
}