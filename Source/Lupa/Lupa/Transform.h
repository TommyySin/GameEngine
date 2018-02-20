#include <stdio.h>
#include "BaseComponent.h"
#include <SFML/Graphics.hpp>

class Transform : public BaseComponent {
public:
	Transform() : m_Position(), m_Rotation(), m_Scale(1, 1) {}
	void Update();
	sf::Vector2f m_Position;
	float m_Rotation;
	sf::Vector2f m_Scale;

	sf::Transform transformMatrix;
};
