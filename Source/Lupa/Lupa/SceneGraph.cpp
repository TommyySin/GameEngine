#include "SceneGraph.h"

// Initialize our static unique objectID generator
SceneGraph::SceneGraph()
{
	nextObjectID = 0;
	m_Objects.clear();
}

void SceneGraph::Update(float msec) {
	for (std::map<int, GameObject*>::iterator i = m_Objects.begin(); i != m_Objects.end(); ++i) {
		(i->second)->Update(msec);
	}
}

GameObject* SceneGraph::CreateObject()
{
	GameObject* newObj = new GameObject(nextObjectID++);
	m_Objects[newObj->GetObjectID()] = newObj;

	return newObj;
}