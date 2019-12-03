#include "collisionmanager.h"

bool CollisionManager::collidesWith(sf::Sprite& player, Enemy& obj2)
{
	//get the bounding box of the ship
	sf::FloatRect playerShip;
	//top left
	playerShip.left = player.getPosition().x + 24;
	playerShip.top = player.getPosition().y + 24;
	//bottom right
	playerShip.width = player.getGlobalBounds().width - 24;
	playerShip.height = player.getGlobalBounds().height - 24;

	//get the bounding box of the alien
	sf::FloatRect alien;
	//top left
	alien.left = obj2.getSprite().getPosition().x;
	alien.top = obj2.getSprite().getPosition().y;
	//bottom right
	alien.width = obj2.getSprite().getGlobalBounds().width;
	alien.height = obj2.getSprite().getGlobalBounds().height;

	//std::cout << "Ship left: " << ship.left << " " << "Ship top: " << ship.top << std::endl;
	//std::cout << "Alien left: " << alien.left << " " << "Alien top: " << alien.top << std::endl;

	return playerShip.intersects(alien);

}

bool CollisionManager::collidesWith(Bullet& obj1, Enemy& obj2)
{
	//get the bounding box of the ship
	sf::FloatRect bullet;
	//top left
	bullet.left = obj1.getSprite().getPosition().x + 16;
	bullet.top = obj1.getSprite().getPosition().y + 16;
	//bottom right
	bullet.width = obj1.getSprite().getGlobalBounds().width;
	bullet.height = obj1.getSprite().getGlobalBounds().height;

	//get the bounding box of the alien
	sf::FloatRect alien;
	//top left
	alien.left = obj2.getSprite().getPosition().x;
	alien.top = obj2.getSprite().getPosition().y;
	//bottom right
	alien.width = obj2.getSprite().getGlobalBounds().width;
	alien.height = obj2.getSprite().getGlobalBounds().height;

	//std::cout << "Ship left: " << ship.left << " " << "Ship top: " << ship.top << std::endl;
	//std::cout << "Alien left: " << alien.left << " " << "Alien top: " << alien.top << std::endl;

	return bullet.intersects(alien);

}