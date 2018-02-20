#include "Transform.h"

void Transform::Update() {
	// Change later to only happen when my transform changes.
	sf::Transform Model;
	//Model = glm::mat4(1.0f);
	Model.translate(m_Position.x, m_Position.y);
	Model.rotate(m_Rotation);
	Model.scale(m_Scale.x, m_Scale.y);
	transformMatrix = Model;
}