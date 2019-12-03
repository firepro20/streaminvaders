#include "enemy.h"
#include <stdio.h>
#include <iostream>

//using namespace Textures;

//const float Enemy::enemySpeed = 10.f;
//float direction = 1.f;
//Enemy alienArray[NUMBER_OF_ALIENS];

// Default Constructor

Enemy::Enemy() 
{
	/*
	//set alive
	mIsAlive = true;
	mIsShooting = false;
	//set speed
	enemySpeed = 10.f;
	// Load an enemy texture
	if (!mEnemyTexture.loadFromFile("Media/Textures/PixelSpaceships/red_01.png")) {
		// Handle loading error
		std::cout << "Oh No! File not loaded." << std::endl;
	}

	//scale sprite and set texture so we know size
	enemySprite.setTexture(mEnemyTexture);
	*/
}


//constructor sets ID number, loads sprite
Enemy::Enemy(const int id, float sp)
{
	enemyID = id;
	//set alive
	mIsAlive = true;
	
	//set speed
	enemySpeed = sp;
	mIsShooting = false;

	// Load an enemy texture
	if (!mEnemyTexture.loadFromFile("Media/Textures/PixelSpaceships/red_01.png")) {
		// Handle loading error
		std::cout << "Oh No! File not loaded." << std::endl;
	}

	//scale sprite and set texture so we know size
	enemySprite.setTexture(mEnemyTexture);
}

// Enemy Loader
/*
void Enemy::enemyLoader(int noOfAliens, Enemy enemyList[NUMBER_OF_ALIENS]) { // might add xPosition;yPosition
	
	for (int i = 0; i < noOfAliens; i++)
	{
		//Enemy alien(i, 10.f); // speed issue
		//alien.setLocation(i * 100.f + 50.f, alien.getSprite().getGlobalBounds().height / 2);
		//alienArray[i] = Enemy (i, 10.f);
		//alienArray.push_back(alien);
		enemyList[i].setLocation(i * 100.f + 50.f, enemyList[i].getSprite().getGlobalBounds().height / 2);
	}
}
*/
void Enemy::setLocation(float xPosition, float yPosition) {
	enemySprite.setPosition(xPosition, yPosition);
}

sf::Sprite& Enemy::getSprite()
{
	return enemySprite;
}

void Enemy::kill()
{
	mIsAlive = false;
}

bool Enemy::isAlive()
{
	return mIsAlive;
}

float Enemy::getSpeed() const
{
	return enemySpeed;
}

void Enemy::draw(sf::RenderWindow& window) {
	enemySprite.setTexture(mEnemyTexture);
	window.draw(enemySprite);
}

sf::Vector2f Enemy::getLocation() {
	sf::Vector2f position = enemySprite.getPosition();
	return position;
}

int Enemy::getID() {
	return enemyID;
}

// Old Loader
/* Old Loader
void Enemy::load() {
	if (!mEnemyTexture.loadFromFile("Media/Textures/PixelSpaceships/red_01.png")) {
		// Handle loading error
		std::cout << "Oh No! File not loaded." << std::endl;
	}


	enemyInstantiator(4, 100.f, 50.f);
}
*/

// Old Instantiator that was called from loader
/* Old Enemy Instantiator
void Enemy::enemyInstantiator(int noOfEnemies, float xPosition, float yPosition) {
	sf::Sprite tempEnemy;
	int tracker = 0;
	float yOffset = 50.f;
	float xOffset = 60.f;

	for (int i = 0; i < noOfEnemies; i++) {
		tempEnemy.setTexture(mEnemyTexture);
		tempEnemy.setOrigin(24.f, 24.f);
		tempEnemy.setPosition(xPosition + (i * xOffset), yPosition);
		tempEnemy.setRotation(180.f);
		if (i >= noOfEnemies / 2) {
			// set position for remainder, problem is that every loop is overiding position and drawing last batch of 5
			for (int j = 0; j < noOfEnemies / 2; j++) {
				tempEnemy.setTexture(mEnemyTexture);
				tempEnemy.setOrigin(24.f, 24.f);
				tempEnemy.setPosition(xPosition + (j * xOffset), yPosition + yOffset);
				tempEnemy.setRotation(180.f);
				std::cout << "Enemy inside 2nd for loop position " << tempEnemy.getPosition().x << " " << tempEnemy.getPosition().y << std::endl;
				// we were not pushing each and every tempEnemy but only the last one when exiting the for loop, therefore we were only printing the last one
				mEnemies.push_back(tempEnemy);
				tracker++;
				if (tracker >= noOfEnemies/2) {
					return;
				}
			}
		}
		std::cout << "Enemy inside 1st for loop position " << tempEnemy.getPosition().x << " " << tempEnemy.getPosition().y << std::endl;
		mEnemies.push_back(tempEnemy);
	}
}
*/

// Enemy Behaviour with vector of Sprites
/*
void Enemy::enemyBehaviour(std::vector<sf::Sprite>& enemyList) {
	
	//sf::Sprite tempEnemy;
	sf::Vector2f enemyMovement(1.f, 0.f); 
	float yOffset = 50.f;
	float xOffset = 60.f;
	for (sf::Sprite& enemy : enemyList) // CAUTION & solved everything again - lesson in C++, if we don't get address, we always create a copy and modify it, which is not what we want
	{
		std::cout << "Direction before working move " << direction << std::endl;
		enemy.move(enemyMovement * direction); // Issue detected direction only changing sign if greater or less than screen bounds once
		if (enemy.getPosition().x + enemy.getLocalBounds().width / 2 > 640.f ||
			enemy.getPosition().x - enemy.getLocalBounds().width / 2 < 0.f) { // can be improved by calling getWidth method
			direction = -(direction);
			
			std::cout << "Direction inside if statement " << direction << std::endl;
			// another for loop move all down by yOffset
			for (sf::Sprite& enemy : enemyList) {
				enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y + yOffset);
				//enemy.move(0.f, enemy.getPosition().y + yOffset);
			}
			//enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y + yOffset); // y axis is inverted in SFML
			return;
		}
		
		if (enemy.getPosition().y > 50.f) {
			//removeEnemy(enemy);
			// ALIVE is false, then draw based on whether alien is alive or not
			
		}

		/*
		if (enemy.getPosition().x - enemy.getLocalBounds().width / 2 <= 0.f) {
			direction = -direction;
			//enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y + yOffset);
		}
		
		//std::cout << "Direction now has value of " << direction << std::endl;
		std::cout << enemy.getPosition().x << " " << enemy.getPosition().y << std::endl;
		/*
		std::cout << "Temp Enemy has " << enemy.getPosition().x << " " << enemy.getPosition().y << std::endl;
		enemy.move(10.f, 0.f);
		std::cout << "Temp Enemy has " << enemy.getPosition().x << " " << enemy.getPosition().y << std::endl;
		
	}
	/*
	for (auto it = enemyList.begin(); it != enemyList.end();)
	{
		//enemyMovement.x += enemySpeed;
		tempEnemy = *it;
		cout << "Temp Enemy has for iterator " << tempEnemy.getPosition().x << " " << tempEnemy.getPosition().y << endl;

		/*
		if (tempEnemy.getPosition().x + tempEnemy.getLocalBounds().width/2 > windowWidth) {
			direction = -direction;
			tempEnemy.setPosition(tempEnemy.getPosition().x, tempEnemy.getPosition().y + yOffset); // y axis is inverted in SFML
		}
		if (tempEnemy.getPosition().x - tempEnemy.getLocalBounds().width / 2 < 0.f) {
			direction = -direction;
			tempEnemy.setPosition(tempEnemy.getPosition().x, tempEnemy.getPosition().y + yOffset);
		}
		tempEnemy.move(enemyMovement * direction);

	}
	*/
	//enemyMovement.x += enemySpeed;
	// Pseudo 
	/*
	if we are at end of move rotation, change direction (-/+) from current position
	and increment position by move.
	
}
*/

// Enemy Update and Render
/*

void Enemy::enemyMovement(Enemy enemyList[NUMBER_OF_ALIENS]) {
	sf::Vector2f enemyMovement(1.f, 0.f);
	float yOffset = 50.f;
	float xOffset = 60.f;
	for (int i = 0; i < NUMBER_OF_ALIENS; i++) // CAUTION & solved everything again - lesson in C++, if we don't get address, we always create a copy and modify it, which is not what we want
	{
		std::cout << "Direction before working move " << direction << std::endl;
		enemyList[i].getSprite().move(enemyMovement * direction); // Issue detected direction only changing sign if greater or less than screen bounds once
		if (enemyList[i].getSprite().getPosition().x + enemyList[i].getSprite().getLocalBounds().width / 2 > 640.f ||
			enemyList[i].getSprite().getPosition().x - enemyList[i].getSprite().getLocalBounds().width / 2 < 0.f) { // can be improved by calling getWidth method
			direction = -(direction);

			std::cout << "Direction inside if statement " << direction << std::endl;
			// another for loop move all down by yOffset
			for (int i = 0; i < NUMBER_OF_ALIENS; i++) {
				enemyList[i].getSprite().setPosition(enemyList[i].getSprite().getPosition().x, enemyList[i].getSprite().getPosition().y + yOffset);
				//enemy.move(0.f, enemy.getPosition().y + yOffset);
			}
			//enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y + yOffset); // y axis is inverted in SFML
			return;
		}
	}
}

void Enemy::update(Enemy enemyList[NUMBER_OF_ALIENS]) {
	enemyMovement(enemyList); // issue cause this is expecting vector and is array instead
	//enemyBehaviour(mEnemies);
}

void Enemy::render(Enemy enemyList[NUMBER_OF_ALIENS], sf::RenderWindow& window) {
	
	for (int i = 0; i < NUMBER_OF_ALIENS; i++) { // issue cause this is expecting vector and is array instead
		if(enemyList[i].isAlive())
		window.draw(enemyList[i].enemySprite);
	}
	
	/*
	for (int i = 0; i < alienArray.size(); i++)
	{
		sf::Sprite temp = alienArray.at(i);
		window.draw(temp);
	}
	
}

*/