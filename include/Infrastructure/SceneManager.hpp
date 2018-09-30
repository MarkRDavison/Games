#ifndef INCLUDED_ASCENDANCE_INFRASTUCTURE_SCENE_MANAGER_HPP_
#define INCLUDED_ASCENDANCE_INFRASTUCTURE_SCENE_MANAGER_HPP_

#include <Infrastructure/Scene.hpp>

namespace inf {

	class SceneManager {
	public:
		SceneManager();
		~SceneManager();

		void update(float _delta);
		bool handleEvent(const sf::Event& _event);
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const ;
		
		void refresh(void);

		void pushScene(Scene *_scene);
		void removeScene(Scene *_scene);
		void clearScenes(void);
		Scene *popScene(void);

	private:
		std::vector<Scene *> m_Scenes;
		std::vector<Scene *> m_NewlyAddedScenes;
		std::vector<Scene *> m_NewlyRemovedScenes;
	};
}

#endif // INCLUDED_ASCENDANCE_INFRASTUCTURE_SCENE_MANAGER_HPP_