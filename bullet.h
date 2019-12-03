#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#pragma once


class Bullet
{
public:
	//constructor sets ID number, loads sprite
	Bullet(const int, float);
	sf::Sprite& getSprite();
	void setLocation(float, float);
	sf::Vector2f getLocation();
	void kill();
	bool isAlive();
	void spawn(bool);
	bool isHit();
	void bulletHit(bool status);
	//draw the sprite
	void draw(sf::RenderWindow& win);
private:
	sf::Sprite bulletSprite;
	sf::Texture bulletTexture;
	bool alive;
	bool hit;
};