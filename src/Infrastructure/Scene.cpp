#include <Infrastructure/Scene.hpp>

namespace inf {
	Scene::Scene(const std::string& _name) :
		Name(_name) {
	}

	Scene::~Scene() {
	}

	void Scene::remove(void) {
		m_ToRemove = true;
	}
	bool Scene::getNeedsRemoval(void) const {
		return m_ToRemove;
	}
	void Scene::setDeleteOnRemove(bool _deleteOnRemove) {
		m_DeleteOnRemove = _deleteOnRemove;
	}
	bool Scene::getDeleteOnRemove(void) const {
		return m_DeleteOnRemove;
	}

}