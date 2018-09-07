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
		for (unsigned i = m_Scenes.size(); i-- > 0; ){
			if (m_Scenes[i]->handleEvent(_event)) {
				return true;
			}
		}
		return false;
	}

	void SceneManager::draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const {
		for (const auto& scene : m_Scenes) {
			scene->draw(_target, _states, _alpha);
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