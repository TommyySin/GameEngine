#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject() { parent = nullptr; }
	~GameObject(void);
	void SetTransform(const sf::Vector3f &matrix) { transform = matrix; }
	sf::Vector3f GetTransform() { return transform; }
	sf::Vector3f GetWorldTransform() { return worldTransform; }
	void SetParent(GameObject& p) { *parent = p; }
	void AddChild(GameObject* s);
	virtual void Update(float msec);

protected:
	GameObject* parent;
	sf::Vector3f worldTransform;
	sf::Vector3f transform;
	std::vector<GameObject*> children;
};