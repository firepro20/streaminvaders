#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#pragma once



//class Game;
class Enemy
{
public:
	//constructor sets ID number, loads sprite
	Enemy();
	Enemy(const int, float);
	int						getID();
	sf::Sprite&				getSprite();
	void					kill();
	bool					isAlive();
	float					getSpeed() const;
	void					draw(sf::RenderWindow& window);
	//void					load();
	//void					enemyLoader(const int noOfAliens, Enemy enemyList[NUMBER_OF_ALIENS]);
	void					setLocation(float xPosition, float yPosition);
	sf::Vector2f			getLocation();
	//void					enemyInstantiator(int noOfEnemies, float xPosition, float yPosition);
	//void					update(Enemy enemyList[NUMBER_OF_ALIENS]);
	//void					render(Enemy enemyList[NUMBER_OF_ALIENS], sf::RenderWindow& window);

private:
	
	//void					enemyBehaviour(std::vector<sf::Sprite>& enemyList);
	//void					enemyMovement(std::vector<Enemy>& enemyList);
	//void					enemyMovement(Enemy enemyList[NUMBER_OF_ALIENS]);

private:
	
	
	sf::Texture				mEnemyTexture;
	sf::Sprite				enemySprite;
	
	
	//std::vector<Enemy>		alienArray;
	//std::vector<sf::Sprite> mEnemies;
	sf::RectangleShape		mEnemyBounds;

	//sf::RenderWindow		mWindow; --> Removed this from here and everything worked no more enormous errors

	int						enemyID;
	bool					mIsShooting;
	bool					mIsAlive;
	float					enemySpeed;

	// Classes
	//Game* mGame; // this is where issue is occuring
	//Game*
	//Game* game;
	//Game* game = Game::getInstance();
	
};

