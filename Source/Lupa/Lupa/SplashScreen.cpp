#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow & renderWindow) 
{
	sf::Texture image;

	if (image.loadFromFile("../../../Assets/image/SplashScreen.jpg") != true) { return; }
	sf::Sprite sprite;
	sprite.setTexture(image);
	//sprite.setScale(sprite.getScale().x, sprite.getScale().y);

	renderWindow.draw(sprite);
	renderWindow.display();
	sf::Event event;
	while (Lupa::_gameState != Lupa::Initialized)
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed) { return; }
		}
	}
}