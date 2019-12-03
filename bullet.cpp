#include "bullet.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Bullet::Bullet(const int id, float speed)
{
	//alive
	alive = false;

	//load a sprite
	if (!bulletTexture.loadFromFile("Media/Textures/PixelSpaceships/Projectiles/projectile-blue.png"))
		throw invalid_argument("Bullet not loaded!");

	// scale
	bulletSprite.scale(sf::Vector2f(0.8f, 0.8f));
	// rotate
	bulletSprite.setRotation(-90.f);
	//bulletSprite.setOrigin(16.f, 16.f);
}

sf::Sprite& Bullet::getSprite()
{
	return bulletSprite;
}

void Bullet::setLocation(float xpos, float ypos)
{
	bulletSprite.setPosition(xpos, ypos);
}

sf::Vector2f Bullet::getLocation() {
	sf::Vector2f position = bulletSprite.getPosition();
	return position;
}

void Bullet::kill()
{
	alive = false;
}

bool Bullet::isAlive()
{
	return alive;
}

void Bullet::spawn(bool status)
{
	alive = status;
}

bool Bullet::isHit() {
	return hit;
}

void Bullet::bulletHit(bool status) {
	hit = status;
}

void Bullet::draw(sf::RenderWindow& win)
{
	//set texture
	bulletSprite.setTexture(bulletTexture);
	win.draw(bulletSprite);
}