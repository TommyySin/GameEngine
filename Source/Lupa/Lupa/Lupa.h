#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SplashScreen.h"
#include "GameObject.h"

class Lupa
{
public:
	static void Start();
	static void Initialize();
	enum GameState {
		Uninitialized,
		ShowingSplash,
		Initialized,
		Paused,
		ShowingMenu,
		Playing,
		Exiting
	};

	static GameState _gameState;
	static sf::RenderWindow* _mainWindow;
	static GameObject* _gameObject;

private:
	static bool IsExiting();
	static void GameLoop();
};