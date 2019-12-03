#include "game.h"
#include <stdio.h>
#include <iostream>

//#define NUMBER_OF_ALIENS 4

//using namespace std;
//using namespace Textures;

/*

const float Game::playerSpeed = 200.f; // playerconnection class

const float Game::enemySpeed = 150.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f); // 60 fps
*/
// Enemy

//Enemy alienArray[NUMBER_OF_ALIENS];

Game* Game::instance = 0;

Game* Game::getInstance() {
	if (instance == 0) {
		instance = new Game();
	}
	return instance;
}

int Game::getWindowWidth() {
	return windowWidth;
}

int Game::getWindowHeight() {
	return windowHeight;
}

// Game Initialisation
/*
Game::Game()
	: mWindow(sf::VideoMode(windowWidth, windowHeight), "SFML Application", sf::Style::Close)
	//, mPlayerTexture()
	//, mPlayer() more than one player what happens?
	, mBackgroundTexture()
	, mBackground()
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
	, mIsShooting(false)
{

	/* Handled in Resource */
	// Loads from file and handles error just in case
	/*
	if (!mTexture.loadFromFile("Media/Textures/PixelSpaceships/blue_01.png"))
	{
		// Handle loading error
	}

	// Set Texture and Position
	mPlayer.setTexture(mTexture);
	mPlayer.setOrigin(24.f, 24.f);
	mPlayer.setPosition(100.f, 100.f);
	*/

	/* Currently not working, revert to simple method
	// Loading Resources

	// Try to load resources
	ResourceHolder<sf::Texture, Textures::ID> textures;

	try
	{
		textures.load(Textures::Background, "Media/Textures/Desert.png");
		//textures.load(Textures::Spaceship, "Media/PixelSpaceships/blue_01.png"); // change to spaceshipblue01
	}
	catch (std::runtime_error & e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		//return 1;
	}
	

	if (!mPlayerTexture.loadFromFile("Media/Textures/PixelSpaceships/blue_01.png"))
	{
		// Handle loading error
	}
	if (!mBackgroundTexture.loadFromFile("Media/Textures/Space.jpg")) {
		// Handle loading error
	}

	// Loading Enemy

	
	enemy.enemyLoader(NUMBER_OF_ALIENS, alienArray);

	//enemy.load(); //Load enemies somewhere else

	mBackground.setTexture(mBackgroundTexture);
	mBackground.setOrigin(windowWidth / 2, windowHeight / 2);
	mBackground.setPosition(windowWidth / 2, windowHeight / 2);

	// Set Texture and Position
	mPlayer.setTexture(mPlayerTexture);
	mPlayer.setOrigin(24.f, 24.f);
	mPlayer.setPosition(windowWidth/2, windowHeight/2);

	//enemy.enemyInstantiator(2, 100.f, 50.f);
	//enemyInstantiator(10, 100.f, 150.f);
	
	// Statistics Initialisation
	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}
*/



/*
// Creates two rows of enemies: takes even noOfEnemies, start xPosition and yPosition
void Game::enemyInstantiator(int noOfEnemies, float xPosition, float yPosition) {
	
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
			for (int j = 0; j < noOfEnemies/2; j++) {
				tempEnemy.setTexture(mEnemyTexture);
				tempEnemy.setOrigin(24.f, 24.f);
				tempEnemy.setPosition(xPosition + (j * xOffset), yPosition + yOffset);
				tempEnemy.setRotation(180.f);
				cout << "Enemy inside 2nd for loop position " << tempEnemy.getPosition().x << " " << tempEnemy.getPosition().y << endl;
				// we were not pushing each and every tempEnemy but only the last one when exiting the for loop, therefore we were only printing the last one
				mEnemies.push_back(tempEnemy);
				tracker++;
				if (tracker >= 5) {
					return;
				}
			}
		}
		cout << "Enemy inside 1st for loop position " << tempEnemy.getPosition().x << " " << tempEnemy.getPosition().y << endl;
		mEnemies.push_back(tempEnemy);
	}
}
*/

// Run Method
/*
void Game::run()
{
	// Measure elapsed time
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		// Puts the time counter back to zero and also returns the time elapsed since the clock was started
		sf::Time deltaTime = clock.restart();
		timeSinceLastUpdate += deltaTime;
		while (timeSinceLastUpdate > TimePerFrame) // fixed time steps
		{
			timeSinceLastUpdate -= TimePerFrame; // solves problem with variable delta time, each frame is unique

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(deltaTime);
		render();
	}
}
*/

// Handles user input
/*
void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}
*/

// Handle Player Input
/*
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A || key == sf::Keyboard::Left) 
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D || key == sf::Keyboard::Right)
		mIsMovingRight = isPressed;
	else if (key == sf::Keyboard::Space) {
		mIsShooting = isPressed;
	}
}
*/

// Update game logic
/*
void Game::update(sf::Time elapsedTime)
{
	// Player 1 movement
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= playerSpeed;
	if (mIsMovingDown)
		movement.y += playerSpeed;
	if (mIsMovingLeft)
		movement.x -= playerSpeed;
	if (mIsMovingRight)
		movement.x += playerSpeed;
	// shooting logic


	// Possibly this will be the data that needs to be sent to server
	mPlayer.move(movement * elapsedTime.asSeconds()); // Time.deltaTime frame independent movement
		
	// for each player eventually
	screenBound(mPlayer);
	// screenbound enemies or else check that they do not go off bounds and change direction
	
	// for each enemy eventually
	enemy.update(alienArray);
	

}
*/

/*
// Handles enemy movement
void Game::enemyBehaviour(std::vector<sf::Sprite>& enemyList, sf::Time deltaTime)
{
	float direction = 1.f;
	sf::Sprite tempEnemy;
	sf::Vector2f enemyMovement(0.f, 0.f);
	float yOffset = 50.f;
	float xOffset = 60.f;
	for (sf::Sprite enemy : enemyList) // equivelant of for each
	{
		cout << "Temp Enemy has " << enemy.getPosition().x << " " << enemy.getPosition().y << endl;
		enemy.move(10.f * deltaTime.asSeconds(), 0.f);
		cout << "Temp Enemy has " << enemy.getPosition().x << " " << enemy.getPosition().y << endl;
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
		tempEnemy.move(enemyMovement * direction * deltaTime.asSeconds());
		
	}
	*/
	//enemyMovement.x += enemySpeed;
	// Pseudo 
	/*
	if we are at end of move rotation, change direction (-/+) from current position
	and increment position by move.
	
}
*/

// Bounds within the window
/*

void Game::screenBound(sf::Sprite& gameObject) 
{
	// X-Axis
	if (gameObject.getPosition().x - gameObject.getLocalBounds().width/2 < 0)
		gameObject.setPosition(0.f + gameObject.getLocalBounds().width/2, gameObject.getPosition().y);
	if (gameObject.getPosition().x + gameObject.getLocalBounds().width/2 > windowWidth)
		gameObject.setPosition(windowWidth - gameObject.getLocalBounds().width / 2, gameObject.getPosition().y);
	// Y-Axis
	if (gameObject.getPosition().y - gameObject.getLocalBounds().height / 2 < 0)
		gameObject.setPosition(gameObject.getPosition().x, 0.f + gameObject.getLocalBounds().height / 2);
	if (gameObject.getPosition().y + gameObject.getLocalBounds().height / 2 > windowHeight)
		gameObject.setPosition(gameObject.getPosition().x, windowHeight - gameObject.getLocalBounds().height / 2);
	// To not get jitter effect, screen dimensions need to be included.
}
*/

// Render
/*
void Game::render() // This is the engine, it should be responsible for calling render methods for each class
{
	// Remember draw order is important
	mWindow.clear();
	mWindow.draw(mBackground);
	mWindow.draw(mPlayer);
	mWindow.draw(mStatisticsText);
	
	enemy.render(alienArray, mWindow);
	/*
	for (int i = 0; i < mEnemies.size(); i++) 
	{
		sf::Sprite temp = mEnemies.at(i);
		mWindow.draw(temp);
	}
	

	mWindow.display();
}
*/

// Updates any statistics we have in game
/*
void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + std::to_string(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}
*/


/*
int main() {
	
	cout << "Starting SFML.." << endl;

	// Window Initialisation
	sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Application");

	// Circle Shape Initialisation
	sf::CircleShape shape;
	shape.setRadius(40.f);
	shape.setOrigin(40.f, 40.f);
	shape.setPosition(256.f, 256.f);
	shape.setFillColor(sf::Color::Red);

	// Window Event Handling
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close;
			}
		}
		// While window exists, clear past frame, draw contents for new frame and display it
		window.clear();
		window.draw(shape);
		window.display();
	}

	cout << "Setting up SFML complete!" << endl;

}
*/