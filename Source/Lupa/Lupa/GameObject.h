#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "BaseComponent.h"
#include "Transform.h"

class GameObject
{
public:
	GameObject(int uniqueID) : m_UniqueID(uniqueID), parent(NULL) {}
	~GameObject(void);
	int GetObjectID() const { return m_UniqueID; }
	void SetTransform(const sf::Transform &matrix) { transform = matrix; }
	sf::Transform GetTransform() { return transform; }
	sf::Transform GetWorldTransform() { return worldTransform; }
	void SetParent(GameObject& p) { *parent = p; }
	void AddChild(GameObject* s);
	virtual void Update(float msec);
	void AddComponent(BaseComponent* component);


protected:
	int m_UniqueID;
	GameObject* parent;
	sf::Transform worldTransform;
	sf::Transform transform;
	std::vector<GameObject*> children;
	std::vector<BaseComponent*> m_Components;
};