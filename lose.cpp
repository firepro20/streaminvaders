#include "lose.h"

Lose::Lose()
{
	// Load gameOver to display
	if (!loseTexture.loadFromFile("Media/Textures/gameover.jpg"))
		throw std::invalid_argument("Game over screen not loaded!");

	//create sprite and scale
	loseSprite.setTexture(loseTexture);
	loseSprite.scale(sf::Vector2f(1, 1));
	loseSprite.setPosition(100, 100);
}

sf::Sprite& Lose::getSprite()
{
	return loseSprite;
}

void Lose::setLocation(float xpos, float ypos)
{
	loseSprite.setPosition(xpos, ypos);
}

void Lose::draw(sf::RenderWindow& win)
{
	//set texture
	loseSprite.setTexture(loseTexture);
	win.draw(loseSprite);
}