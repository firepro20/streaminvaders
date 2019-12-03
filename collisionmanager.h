#pragma once
#include "enemy.h" // might cause issues of circular dependency
#include "bullet.h"
#include <iostream>

class CollisionManager
{
public:
	static bool collidesWith(sf::Sprite& player, Enemy&);
	static bool collidesWith(Bullet&, Enemy&);

private:
};