#pragma once
#include <iostream>
#include <map>
#include "GameObject.h"


class SceneGraph 
{
public:
	SceneGraph::SceneGraph();
	GameObject* CreateObject();

	void Update(float msec);
	
private:
	std::map <int, GameObject*> m_Objects;
	int nextObjectID; 
};