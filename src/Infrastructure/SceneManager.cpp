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
			if (scene->getNeedsRemoval()) {
				removeScene(scene);
			}
		}

		refresh();
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

	void SceneManager::refresh(void) {
		if (!m_NewlyRemovedScenes.empty()) {
			for (Scene *sceneToRemove : m_NewlyRemovedScenes) {
				for (unsigned i = 0; i < m_Scenes.size(); ++i) {
					if (sceneToRemove == m_Scenes[i]) {
						m_Scenes.erase(m_Scenes.begin() + i);
						if (sceneToRemove->getDeleteOnRemove()) {
							delete sceneToRemove;
						}
						break;
					}
				}
			}
			m_NewlyRemovedScenes.clear();
		}
		if (!m_NewlyAddedScenes.empty()) {
			for (Scene *sceneToAdd : m_NewlyAddedScenes) {
				m_Scenes.push_back(sceneToAdd);
			}
			m_NewlyAddedScenes.clear();
		}
	}

	void SceneManager::pushScene(Scene *_scene) {
		m_NewlyAddedScenes.push_back(_scene);
	}

	void SceneManager::removeScene(Scene* _scene) {
		m_NewlyRemovedScenes.push_back(_scene);
	}

	Scene *SceneManager::popScene(void) {
		const auto popped = m_Scenes.back();
		m_Scenes.erase(m_Scenes.begin() + m_Scenes.size() - 1);
		return popped;
	}
}