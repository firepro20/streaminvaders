#include "win.h"

Win::Win()
{
	// GameOver Texture
	if (!winTexture.loadFromFile("Media/Textures/youwin.png"))
		throw std::invalid_argument("You win screen not loaded!");

	//create sprite and scale
	winSprite.setTexture(winTexture);
	winSprite.scale(sf::Vector2f(1, 1));
	winSprite.setPosition(100, 100);
}

sf::Sprite& Win::getSprite()
{
	return winSprite;
}

void Win::setLocation(float xpos, float ypos)
{
	winSprite.setPosition(xpos, ypos);
}

void Win::draw(sf::RenderWindow& win)
{
	//set texture
	winSprite.setTexture(winTexture);
	win.draw(winSprite);
}

