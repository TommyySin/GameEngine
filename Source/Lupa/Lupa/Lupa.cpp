#include "Lupa.h"

Lupa::GameState Lupa::_gameState;
sf::RenderWindow* Lupa::_mainWindow;
GameObject* Lupa::_gameObject;

void Lupa::Start(void)
{
	if (_gameState != Uninitialized) return;
	_mainWindow->create(sf::VideoMode(1024, 768, 32), "Don't hit me");
	_gameState = Lupa::ShowingSplash;
	SplashScreen::Show(*_mainWindow);

	while (!IsExiting())
	{
		GameLoop();
	}
	_mainWindow->close();
}

bool Lupa::IsExiting(void)
{
	return false;
}

void Lupa::Initialize(void)
{
	_mainWindow = new sf::RenderWindow();
	_gameObject = new GameObject();
}

void Lupa::GameLoop(void)
{

}
