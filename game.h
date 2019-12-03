#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
//#include "enemy.h"

#pragma once



class Game //: private sf::NonCopyable // was causing issues when creating game instance in enemy
{
public:
	//Game();
	//void					run();

	int						getWindowWidth();
	int						getWindowHeight();

	/* Static access method. */
	static Game* getInstance();

private:

	/* Private constructor to prevent instancing. */
	//Game();

	//void					processEvents();
	//void					update(sf::Time elapsedTime);
	//void					render();
	//void					screenBound(sf::Sprite& gameObject);
	//void					updateStatistics(sf::Time elapsedTime);
	//void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	

private:

	/* Here will be the instance stored. */
	static Game* instance;

	
	static const int		windowWidth = 640;
	static const int		windowHeight = 480;
	//static const float		playerSpeed;
	//static const float		enemySpeed;
	//static const sf::Time	TimePerFrame;

	//sf::RenderWindow		mWindow;
	//sf::Texture				mPlayerTexture;
	//sf::Sprite				mPlayer;
	//sf::Texture				mBackgroundTexture;
	//sf::Sprite				mBackground;

	//sf::Font				mFont;
	//sf::Text				mStatisticsText;
	//sf::Time				mStatisticsUpdateTime;

	//std::size_t				mStatisticsNumFrames;
	//bool					mIsMovingUp;
	//bool					mIsMovingDown;
	//bool					mIsMovingRight;
	//bool					mIsMovingLeft;
	//bool					mIsShooting;
	
	// Classes
	//Enemy enemy;
};


