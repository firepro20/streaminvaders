#include "game.h" // which will handle only window height
#include "enemy.h"
#include "bullet.h"
#include "collisionmanager.h"
#include "win.h"
#include "lose.h"
#include <iostream>
#include <cassert>

#define NUMBER_OF_ALIENS 8
#define SERVER_PORT 54000 // one port needs to be defined for UDP

struct PlayerMessage {
	int time;
	float x, y;
};

float direction = 1.f;
const float playerSpeed = 200.f;
const float enemySpeed = 100.f;
const float bulletSpeed = 150.f;
const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
const sf::Time tickRate = sf::seconds(1.f / 30.f); // 30 updates per second

sf::Time				mStatisticsUpdateTime;
std::size_t				mStatisticsNumFrames;

bool					mPlayerIsAlive;
bool*					playerAlivePtr;
bool					mIsMovingUp;
bool					mIsMovingDown;
bool					mIsMovingRight;
bool					mIsMovingLeft;
bool					mIsShooting;
bool					mIsServer;
bool					mIsClient;
bool					winState;
bool					gameOver;
bool					serverCreated;

// Network

sf::UdpSocket			socket; // only need one socket, bind this in the beginning both client or server .. use method to switch between send and receive
sf::IpAddress			server;
sf::Sprite				mPlayer; //moved this to global to access position on viewer/client
sf::Sprite*				player;
sf::Vector2f			firstEnemyPosition;
Bullet*					bulletPtr;
int						enemyShotID;
std::string				enemyStatus;
sf::Clock				gameTime;
int						gameTimer;
int*					gameTimerPtr;
std::vector<PlayerMessage> messageHolder;

bool					useServerTime = true;
bool					sendInitialToServer = false;
bool					portBound = false;
bool					enemyCheckOnConnected = false;

// Prototypes
void processEvents(sf::RenderWindow& window);
void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
void screenBound(sf::Sprite& gameObject);
void updateStatistics(sf::Time elapsedTime, sf::Text& statisticsText);
void createEnemies();

void createUdpServer(unsigned short port);
void runUdpClient(unsigned short port);
// Put these methods directly in main loop
//void update(sf::Time elapsedTime);
//void render(sf::RenderWindow& window);

Game* game = Game::getInstance(); // for window dimensions

std::vector<Enemy>* enemyList = new std::vector<Enemy>();


int main()
{
	sf::Texture				mPlayerTexture;
	//sf::Sprite				mPlayer; //moved this to global to access position
	player =				&mPlayer;
	sf::Texture				mBackgroundTexture;
	sf::Sprite				mBackground;
	
	Win win;
	Lose lose;

	enemyShotID = -1; // initialising ID to send to client

	Bullet bullet(0, bulletSpeed);
	bulletPtr = &bullet;
	mPlayerIsAlive = true;
	playerAlivePtr = &mPlayerIsAlive;

	sf::RenderWindow		window(sf::VideoMode(game->getWindowWidth(), game->getWindowHeight()), "Stream Invaders");
	
	//static const sf::Time	TimePerFrame;
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60); // Added this

	if (!mPlayerTexture.loadFromFile("Media/Textures/PixelSpaceships/blue_01.png"))
	{
		// Handle loading error
	}
	if (!mBackgroundTexture.loadFromFile("Media/Textures/Space.jpg")) {
		// Handle loading error
	}
	
	// Set Texture and Position for Background
	mBackground.setTexture(mBackgroundTexture);
	mBackground.setOrigin(game->getWindowWidth() / 2.f, game->getWindowHeight() / 2.f);
	mBackground.setPosition(game->getWindowWidth() / 2.f, game->getWindowHeight() / 2.f);

	// Set Texture and Position for Player
	mPlayer.setTexture(mPlayerTexture);
	mPlayer.setOrigin(24.f, 24.f);
	mPlayer.setPosition(game->getWindowWidth() / 2.f, game->getWindowHeight() - game->getWindowHeight()/8.f);

	//enemy.enemyInstantiator(2, 100.f, 50.f);
	//enemyInstantiator(10, 100.f, 150.f);

	// Statistics Initialisation
	sf::Font				mFont;
	sf::Text				mStatisticsText;
	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);

	// Enemy Creation // Separate method in main
		
	createEnemies();
	
	// Enemy creation with rows
	/*
	int tracker = 0;

	for (int i = 0; i < NUMBER_OF_ALIENS; i++) {
		Enemy alien(i, enemySpeed);
		alien.getSprite().setOrigin(24.f, 24.f);
		alien.getSprite().setPosition(xPosition + (i * xOffset), yPosition);
		alien.getSprite().setRotation(180.f);
		if (i >= NUMBER_OF_ALIENS / 2) {
			// set position for remainder, problem is that every loop is overiding position and drawing last batch of 5
			for (int j = 0; j < NUMBER_OF_ALIENS / 2; j++) {
				
				alien.getSprite().setOrigin(24.f, 24.f);
				alien.getSprite().setPosition(xPosition + (j * xOffset), yPosition + yOffset);
				alien.getSprite().setRotation(180.f);
				//std::cout << "Enemy inside 2nd for loop position " << tempEnemy.getPosition().x << " " << tempEnemy.getPosition().y << std::endl;
				// we were not pushing each and every tempEnemy but only the last one when exiting the for loop, therefore we were only printing the last one
				enemyList->push_back(alien);
				tracker++;
				if (tracker >= NUMBER_OF_ALIENS / 2) {
					break;
				}
			}
		}
		//std::cout << "Enemy inside 1st for loop position " << tempEnemy.getPosition().x << " " << tempEnemy.getPosition().y << std::endl;
		enemyList->push_back(alien);
	}
	*/

	/*
	//create a an array of enemys
	Enemy alienArray = new Enemy[];
	for (int i = 0; i < NUMBER_OF_ALIENS; i++)
	{
		Enemy alien(i, enemySpeed);

		alien.setLocation(i * 50.f + 50.f, alien.getSprite().getGlobalBounds().height / 2);
		alienArray;
	}
	*/

	//game->run();

	// Measure elapsed time
	sf::Clock clock; // -> can actually be used as game time? to determine movement possibly
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Clock tickClock;
	sf::Time timeSinceLastTick = sf::Time::Zero;
	
	char userChoice = NULL;

	// something here or within the window is open needs to happen to select whether to view or play
	// menu needs to happen over here or within

	while (window.isOpen())
	{
		
		if (userChoice == NULL){
			do {

				std::cout << "User Choice - " << userChoice << std::endl;
				std::cout << "Server or client? (s/c)" << std::endl;
				std::cin >> userChoice;
				
			} while (userChoice != 's' && userChoice != 'c');
			// The game clock will keep on restarting until the user makes a decision
			clock.restart(); // This solved issue to start movements and updates at same time once user chooses an option
			tickClock.restart();
			gameTime.restart(); // restarts the main game time
		}
		
		if (userChoice == 's' || userChoice == 'c') { // start of main if  // else start the whole program
			
			window.setTitle("Stream Invaders");
			// game time over here once game starts // frame independent

			// Binding of ports for both client or server
			/*

			// bind the socket to a port
			if (socket.bind(54000) != sf::Socket::Done)
			{
				// Using UDP starts listening on this port
				// whatever happens, bind for both -> will work with two executables running on same network with two different local IPs
			}

			*/

			// Puts the time counter back to zero and also returns the time elapsed since the clock was started
			sf::Time deltaTime = clock.restart();
			if (useServerTime) {
				gameTimer = gameTime.getElapsedTime().asMilliseconds();
			}
			
			std::cout << "Game Time - " << gameTimer << std::endl;
			
			timeSinceLastUpdate += deltaTime;
			while (timeSinceLastUpdate > TimePerFrame) // fixed time steps // userchoice != NULL otherwise it will start immeadiately
			{
				timeSinceLastUpdate -= TimePerFrame; // solves problem with variable delta time, each frame is unique

				processEvents(window);
				//update(TimePerFrame);

				// Start of if server
				if (userChoice == 's'){

					window.setTitle("Stream Invaders Host");
					//if(!serverCreated){ // if problems of continous connection, this needs to place outside of bind
						// create connection
						//createUdpServer(SERVER_PORT); // over here its happening every frame
						//serverCreated = true; // is server actually created though?
					//}

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
					if (mIsShooting) {
						if (!bullet.isAlive()) // && !gameOver
						{
							bullet.spawn(true);
							bullet.setLocation(mPlayer.getPosition().x - 13.f, mPlayer.getPosition().y - 24.f); // mPlayer.getPosition().x + 24 (offset) if origin is not set to center
						}
					}
			
					// ** These two parts need to be put in an if statement, if server, direct movement, if client, move needs to happen with data received 
					// from server (Server - main player streamer; Client - viewer)

					// Possibly this will be the data that needs to be sent to server
					mPlayer.move(movement * TimePerFrame.asSeconds()); // Time.deltaTime frame independent movement

					// for each player eventually
					screenBound(mPlayer);
					// screenbound enemies or else check that they do not go off bounds and change direction

					// **

				} // end of if server
				else {
					window.setTitle("Stream Invaders Viewer");
					// Handle control through incoming network data
					// vector x = datacoming in
					// Hypothetically mPlayer.move(data coming in);

					// bullet spawn
					// setlocation from data packet
					
					//runUdpClient(SERVER_PORT); running every frame
				}

				// Enemy Behaviour // Ideally move to separate method

				sf::Vector2f enemyMovement(1.f, 0.f);
				float yOffset = 30.f;
				float xOffset = 60.f;
				// Be careful with iterators as when deleting it will automatically jump to the next item in vector
				for (std::vector<Enemy>::iterator i = enemyList->begin(); i != enemyList->end(); ++i) // CAUTION & solved everything again - lesson in C++, if we don't get address, we always create a copy and modify it, which is not what we want
				{
					//std::cout << "Direction before working move " << direction << std::endl;
					i->getSprite().move(enemyMovement * direction); // Issue detected direction only changing sign if greater or less than screen bounds once
					if (i->getSprite().getPosition().x + i->getSprite().getLocalBounds().width / 2 > game->getWindowWidth() ||
						i->getSprite().getPosition().x - i->getSprite().getLocalBounds().width / 2 < game->getWindowWidth() - game->getWindowWidth()) { // this will be 0
						direction = -(direction);
						// Time stamp over here for network calculations
						//std::cout << "Direction inside if statement " << direction << std::endl;
						// another for loop move all down by yOffset
						for (std::vector<Enemy>::iterator i = enemyList->begin(); i != enemyList->end(); ++i) {
							i->getSprite().setPosition(i->getSprite().getPosition().x, i->getSprite().getPosition().y + yOffset);
							//enemy.move(0.f, enemy.getPosition().y + yOffset);
						}
						//enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y + yOffset); // y axis is inverted in SFML
						//return 0; // move to separate method
					}

					// This takes care of everything on both sides
					if ((i->getSprite().getPosition().y > game->getWindowHeight() - mPlayer.getLocalBounds().height)) {

						mPlayerIsAlive = false;
						winState = false;
						gameOver = true;

						//removeEnemy(enemy);
						// ALIVE is false, then draw based on whether alien is alive or not
						//std::cout << "Everyone should be dead game over!" << std::endl;
						//return 0; // change state to paused
					}

					// Populates position of first spaceship to be sent to client
					if (i->getID() == 0)
					{
						firstEnemyPosition = i->getLocation();
					}
				}
			}

			updateStatistics(deltaTime, mStatisticsText);
				
			// ** Start of if server
			if (userChoice == 's'){
				for (std::vector<Enemy>::iterator i = enemyList->begin(); i != enemyList->end(); ++i) {
					
					// Test player and alien collision
					if (CollisionManager::collidesWith(mPlayer, *i) && i->isAlive()) { // *i it points to the enemy, and will give me an enemy
						//std::cout << "You're dead!" << std::endl;
						
							mPlayerIsAlive = false;
							winState = false;
							gameOver = true;
						
						//return 0; //-> I'm dead gameOver = true;
					}

					// Test collision between bullets and aliens
					if (CollisionManager::collidesWith(bullet, *i) && i->isAlive())
					{
						i->kill();
						enemyShotID = i->getID();
						//enemyList->erase(i); // issue here, we are trying to do this in order to get rid of rendering problems .. shit just move it out of way
						//i->setLocation(700.f, 10.f);
						bullet.kill();
						bullet.setLocation(700.f, 0.f); // temporary solution for dealing with not actually killing but stop drawing bullet
						// without above line, the bullet will not be drawn but still exist on screen
						bullet.bulletHit(true);
					}
			
					/*
					v.erase(std::remove_if(v.begin(), v.end(), //erase returns it, so it = erase
						[](int i) { return i < 10; }), v.end());
					*/
				}
			}
			// ** end of if server

			int deadEnemies = 0;
			
			for (std::vector<Enemy>::iterator i = enemyList->begin(); i != enemyList->end(); ++i) {
				char buff[20];
				std::size_t found = enemyStatus.find(std::to_string(i->getID()));
				if (!(i->isAlive())) {
					if(!(found != std::string::npos)){ // if it's not in the string, add it
						enemyStatus += std::to_string(i->getID());
						std::cout << "Enemy Status - " << enemyStatus << std::endl;
					}
					deadEnemies++;
				}
				if (deadEnemies >= NUMBER_OF_ALIENS) {
					//std::cout << "You win!" << std::endl;
					if (!gameOver) {
						winState = true;
						gameOver = true;
					}
					// change state to win
					//return 0; // Set state win
				}
			
			}
			//std::cout << "Total Dead Enemies - " << deadEnemies << std::endl; 

			//for (Enemy& enemy : enemyList) {
			//	if (enemy.isAlive()) {
			//		enemy.draw(window);
			//	}
			//}

			//enemy.render(alienArray, mWindow);
			/*
			for (int i = 0; i < mEnemies.size(); i++)
			{
				sf::Sprite temp = mEnemies.at(i);
				mWindow.draw(temp);
			}
			*/

			// Render All
			// Remember draw order is important
			window.clear();

			
			window.draw(mBackground);

			if (bullet.isAlive()) // && !gameOver // for game state and win / lose screen representation
			{
				//draw bullet
				bullet.draw(window);
				//move bullet
				bullet.getSprite().move(0.f, -20);
			}
			// ^ this was put here so bullet is drawn under player

			window.draw(mPlayer);
			window.draw(mStatisticsText);


			for (std::vector<Enemy>::iterator i = enemyList->begin(); i != enemyList->end(); ++i) {
				if (i->isAlive()) {
					i->draw(window);
					//std::cout << "Enemy " << i->getID() << " position - " << i->getLocation().x << " " << i->getLocation().y << std::endl;
				}
			}
						

			//test collision with bullet and boundary
			if (bullet.getSprite().getPosition().y < 0)
				bullet.kill();

			
			// Network
			if (userChoice == 's') { // && tick > 50ms
				
				sf::Time deltaTick = tickClock.restart();
				timeSinceLastTick += deltaTick;
				while (timeSinceLastTick > tickRate) {

					timeSinceLastTick = sf::Time::Zero;
					createUdpServer(SERVER_PORT);

				}
				
			}
			else {
				runUdpClient(SERVER_PORT);
			}

			// State Overlay Sprites
			if (!gameOver) {
				window.display();
			}
			else {
				if (winState) {
					win.getSprite().setOrigin(win.getSprite().getLocalBounds().width / 2.f, win.getSprite().getLocalBounds().height / 2.f);
					win.setLocation(game->getWindowWidth() / 2.f, game->getWindowHeight() / 2.f);
					win.draw(window);
				}
				if (!mPlayerIsAlive || !playerAlivePtr) {
					lose.getSprite().setOrigin(lose.getSprite().getLocalBounds().width / 2.f, lose.getSprite().getLocalBounds().height / 2.f);
					lose.setLocation(game->getWindowWidth() / 2.f, game->getWindowHeight() / 2.f);
					lose.draw(window);
				}
				window.display();
			}
			

		} // end of main second if
	}

	return 0;
}

void createUdpServer(unsigned short port) { // send data to client
	
	// Create a socket to receive a message from anyone
	sf::UdpSocket socket;
	//sf::IpAddress local = sf::IpAddress::getLocalAddress(); // Currently 127.0.0.1 localhost
	//sf::IpAddress receiver = sf::IpAddress::getLocalAddress();
	
	socket.setBlocking(false);
	// I was figuring out and arranging according to example.. set socket non blocking

	// Listen to messages on the specified port
	if (socket.bind(port) != sf::Socket::Done && !portBound) // You bind once
		return; // error
	else {
		portBound = true;
	}
	//std::cout << "Server is listening to port " << port << ", waiting for a connection... " << std::endl;
	
	// Wait for a message
	char in[128];
	std::size_t received;
	sf::IpAddress sender;
	//unsigned short senderPort; we will be receiving and sending data on sa,e port
	
	sf::SocketSelector selector;
	selector.add(socket);

	if (selector.wait(sf::milliseconds(20.f))) { // times out after 20ms // tickrate 43fps
		if (selector.isReady(socket)) {
			if (socket.receive(in, sizeof(in), received, sender, port) != sf::Socket::Done) // blocking
				return;
			//std::cout << "Message received from client " << sender << ": \"" << in << "\"" << std::endl;
		}
	}
	
	// Sends connection established to client
	/*
	const char out[] = "Connection with server established!";
	if (socket.send(out, sizeof(out), sender, port) != sf::Socket::Done)
		return;
	*/
	// acknowledgement of packets
	sf::Packet playerData;
	float playerXPosition = player->getPosition().x;
	float playerYPosition = player->getPosition().y;
	float enemyXPosition  =	firstEnemyPosition.x;
	float enemyYPosition  = firstEnemyPosition.y;
	int timeStamp = gameTime.getElapsedTime().asMilliseconds(); // server time
	//std::string enemyStatus = "26"; // add dead enemies to a string
	
	playerData << timeStamp << playerXPosition << playerYPosition << bulletPtr->isAlive() << enemyShotID << enemyXPosition << enemyYPosition 
			   << enemyStatus << mPlayerIsAlive;
	
	socket.send(playerData, sender, port);
	
	
	// Reset enemy shot ID
	enemyShotID = -1;

}

void runUdpClient(unsigned short port) { // receive data from server

	// Ask for the server address
	server = "127.0.0.1";
	//server = "192.168.0.1";
	//std::cout << server << std::endl;
	/*
	if (server == sf::IpAddress::None){
		do
		{
			std::cout << "Type the address or name of the server to connect to: ";
			std::cin >> server;
		
		} while (server != sf::IpAddress::Any);
	}
	*/
	// Create a socket for communicating with the server
	sf::UdpSocket socket;


	sf::IpAddress recipient = sf::IpAddress::getLocalAddress();
	char data[100] = "Connection with client established!";

	if (socket.send(data, 100, server, port) != sf::Socket::Done && !sendInitialToServer) // if send once dont't send again
	{
		// added up top send this only once
		// error...
	}
	else{
		sendInitialToServer = true;
	}
	
	// Think about putting this globally
	sf::SocketSelector selector;
	selector.add(socket);
	
	if (selector.wait(sf::milliseconds(10.f))) { // not enough time for server to be created with 0.1f // previously was 100

		// received something
		if (selector.isReady(socket)) {

			// Wait for a message
			//char in[128];
			//std::size_t received; // am I using this?
			sf::IpAddress sender;
			sf::Packet playerData; // playerdata1 //playerdata2
			sf::Packet bulletData;
			float playerXPosition;
			float playerYPosition;
			float clientXPosition;
			float clientYPosition;
			float clientEnemyXPosition;
			float clientEnemyYPosition;
			float yEnemyOffset = 50.f;
			float xEnemyOffset = 60.f;
			bool bulletShot;
			bool playerAlive;
			int enemyShotIDReceived;
			std::string enemyStatusReceived;
			int packetTime;
			// predicted position coordinates
			float x_;
			float y_;
			float x_one;
			float y_one;
			float x_final; // interpolated value
			float y_final; // interpolated value

			// third packet
			socket.receive(playerData, sender, port); 
			// first packet - interpolate .. create scenario as tutorial
			
			if (playerData >> packetTime >> playerXPosition >> playerYPosition >> bulletShot >> enemyShotIDReceived >> clientEnemyXPosition >> clientEnemyYPosition 
				>> enemyStatusReceived >> playerAlive) { // if you are able to read
				clientXPosition = playerXPosition;
				clientYPosition = playerYPosition;
				
				//std::cout << "State of player is - " << playerAlive << std::endl;
				//std::cout << "Received from server - " << packetTime << std::endl;
				gameTimer = packetTime;
				useServerTime = false;
				//gameTimerPtr = &packetTime;

				//player->setPosition(clientXPosition, clientYPosition);
				
				// Handles prediction
				PlayerMessage msg;
				msg.time = packetTime;  msg.x = clientXPosition; msg.y = clientYPosition;
				messageHolder.push_back(msg);
				int messageHolderSize = messageHolder.size();
				std::cout << "Message Holder Size - " << messageHolderSize << std::endl;
				if (messageHolder.size() >= 3) {
					const PlayerMessage& msg0 = messageHolder[messageHolderSize - 1];
					const PlayerMessage& msg1 = messageHolder[messageHolderSize - 2];
					const PlayerMessage& msg2 = messageHolder[messageHolderSize - 3];

					//std::cout << "X " << " " << msg0.x << " " << msg1.x << " " << msg2.x << std::endl;
					//std::cout << "Y " << " " << msg0.y << " " << msg1.y << " " << msg2.y << std::endl;
					//std::cout << "Time Stamp " << " " << msg0.time << " " << msg1.time << " " << msg2.time << std::endl;

					/* Linear Model */
					int latency = gameTimer - msg1.time; // this works as it is the latest, if we do 2, then it's like we missed two updates
					float velocity_x = (msg0.x - msg1.x) / (msg0.time - msg1.time); // only prediction for third position
					float velocity_y = (msg0.y - msg1.y) / (msg0.time - msg1.time);
					x_ = msg0.x + velocity_x * latency;
					y_ = msg0.y + velocity_y * latency;
					x_one = msg1.x + velocity_x * latency;
					y_one = msg1.y + velocity_y * latency;
					x_final = x_ * (0.5f) + x_one * (0.5f);
					y_final = y_ * (0.5f) + y_one * (0.5f);
					std::cout << "gameTimer " << gameTimer << " - msg1.time " << msg1.time << " = " << latency << "ms" << std::endl;
					player->setPosition(x_final, y_final); // the interpolated value between two points
				}
				else {
					//player->setPosition(clientXPosition, clientYPosition);
				}
				// end of prediction handling

				if (bulletShot) {
					// - might not need this
					// if not already received
					// once bullet spawned, should be taken care of both sides
					//
					if (!bulletPtr->isAlive()) {
						bulletPtr->spawn(bulletShot);
						bulletPtr->setLocation(clientXPosition - 13.f, clientYPosition - 24.f); // -13.f -24.f // y is inverted in SFML
					}
			
				}
				else {
					if (bulletPtr->isAlive())
						bulletPtr->kill();
				}

				// Dealing with enemy / bullet collision && enemy already dead
				if (enemyShotIDReceived != -1) {
					for (std::vector<Enemy>::iterator i = enemyList->begin(); i != enemyList->end(); ++i) {
						if ((i->getID() == enemyShotIDReceived && i->isAlive())) {
							i->kill();
							enemyShotIDReceived = -1; // reset
						}
					}
				}
				
				// Dealing with enemy already dead when connecting
				//if (!enemyCheckOnConnected){
					//std::cout << "Size of received - " << enemyStatusReceived.size() << std::endl;
					//std::cout << "Content received - " << enemyStatusReceived << std::endl;
					//std::cout << "Content in char - " << enemyStatusReceived.c_str() << std::endl;
					char enemyIds[10]; // this has been optimised from server side, we are now receiving one whole number which is not larger than 10 chars (should be no. of enemy size)
					strcpy_s(enemyIds, enemyStatusReceived.c_str());
					for (std::vector<Enemy>::iterator i = enemyList->begin(); i != enemyList->end(); ++i) {
						for (int j = 0; j < sizeof(enemyIds); j++) {
							if ((i->getID() == (enemyIds[j] - '0')) && i->isAlive() && (enemyIds[j] - '0' >= 0 && enemyIds[j] - '0' <= 8)) { // compare to actual number by subtracting ASCII values from 0 (48), advantage all in order
								//std::cout << "This happened " + j << std::endl;
								i->kill();
							}
						}
					}
					//enemyCheckOnConnected = true; // check once to sync, don't check again
				//}
				
				// Dealing with enemy position
				for (std::vector<Enemy>::iterator i = enemyList->begin(); i != enemyList->end(); ++i) {
					if (i->getID() == 0) {
						i->setLocation(clientEnemyXPosition, clientEnemyYPosition);
					}
					else {
						// set position based on the first with offsets
						i->setLocation((clientEnemyXPosition)+(i->getID() * xEnemyOffset), clientEnemyYPosition);
					}
				}

				// Dealing with player death
				if (!playerAlive) {
					//throw std::invalid_argument("Game should end, player status is " + playerAlive);
					gameOver = true;
					mPlayerIsAlive = false;
					winState = false;
				}
			}
			/*
			if (bulletData >> bulletShot >> clientBulletX >> clientBulletY) {
				if (bulletShot) {
					bulletPtr->spawn(true); // once bullet spawned, should be taken care of both sides
					bulletPtr->setLocation(player->getPosition().x - 13.f, player->getPosition().y - 24.f);
										
					//bulletPtr->draw(window); // client window handled from both client and server what to do if bullet is alive
				}
			}*/
			else { // if(packetTime > gameTimer)
				std::cout << "Failed to read last packet! - Not Predicting" << std::endl;
				//std::cout << "Message Holder size - " << messageHolder.size() << std::endl;
				
				
					//useServerTime = true;
					// Handle error / packet loss // else simulate?
					//std::cout << "Error - failed to read from player data packet!" << std::endl; // this is normal when packet is lost
					// I think I am getting several packet drops as I am receiving and sending from the same PC same port, localhost
				
			}
			// else discard if packettime is less than gameTimer, to discard old data
			// store position update over here

			//unsigned short senderPort;
			//if (socket.receive(in, sizeof(in), received, sender, port) != sf::Socket::Done)
			//	return;
			//std::cout << "Message received from server " << sender << ": \"" << in << "\"" << std::endl;
		}
		// this shouldn't be here, receive stuff should go on client, server just sends
	}
	else {

		// timeout reached, nothing was received 

	}
	// prediction 
	// bullet

}

sf::Packet& operator <<(sf::Packet& packet, const PlayerMessage& msg)
{
	return packet << msg.time << msg.x << msg.y;
}

sf::Packet& operator >>(sf::Packet& packet, PlayerMessage& msg)
{
	return packet >> msg.time >> msg.x >> msg.y;
}

/*
sf::Packet& operator <<(sf::Packet& packet, Bullet& bullet)
{
	return packet << 
}

sf::Packet& operator >>(sf::Packet& packet, Character& character)
{
	return packet >> character.age >> character.name >> character.weight;
}
*/

void processEvents(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event))
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
			window.close();
			break;
		}
	}
}

void handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
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
		
		//std::cout << "Spacebar was pressed!" << std::endl;
	}
}

// Update
/*
void update(sf::Time elapsedTime)
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
	//enemy.update(alienArray);


}
*/

//Render All
/*
void render(sf::RenderWindow& window) // This is the engine, it should be responsible for calling render methods for each class
{
	// Remember draw order is important
	window.clear();
	window.draw(mBackground);
	window.draw(mPlayer);
	window.draw(mStatisticsText);

	//enemy.render(alienArray, mWindow);
	/*
	for (int i = 0; i < mEnemies.size(); i++)
	{
		sf::Sprite temp = mEnemies.at(i);
		mWindow.draw(temp);
	}
	

	window.display();
}
*/

void screenBound(sf::Sprite& gameObject)
{
	// X-Axis
	if (gameObject.getPosition().x - gameObject.getLocalBounds().width / 2 < 0)
		gameObject.setPosition(0.f + gameObject.getLocalBounds().width / 2, gameObject.getPosition().y);
	if (gameObject.getPosition().x + gameObject.getLocalBounds().width / 2 > game->getWindowWidth())
		gameObject.setPosition(game->getWindowWidth() - gameObject.getLocalBounds().width / 2, gameObject.getPosition().y);
	// Y-Axis
	if (gameObject.getPosition().y - gameObject.getLocalBounds().height / 2 < 0)
		gameObject.setPosition(gameObject.getPosition().x, 0.f + gameObject.getLocalBounds().height / 2);
	if (gameObject.getPosition().y + gameObject.getLocalBounds().height / 2 > game->getWindowHeight())
		gameObject.setPosition(gameObject.getPosition().x, game->getWindowHeight() - gameObject.getLocalBounds().height / 2);
	// To not get jitter effect, screen dimensions need to be included.
}

void updateStatistics(sf::Time elapsedTime, sf::Text& statisticsText)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		statisticsText.setString(
			"Frames / Second = " + std::to_string(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void createEnemies() {

	float xPosition = 100.f;
	float yPosition = 50.f;
	float yOffset = 50.f;
	float xOffset = 60.f;

	// New Original Instantiator

	for (int i = 0; i < NUMBER_OF_ALIENS; i++) {
		Enemy alien(i, enemySpeed);
		alien.getSprite().setOrigin(24.f, 24.f);
		alien.setLocation((xPosition)+(i * xOffset), yPosition);
		alien.getSprite().setRotation(180.f);
		enemyList->push_back(alien);
		//enemyStatus[alien.getID()] = true; // 
		//std::cout << "I have " << enemyList->size() << " spaceships" << std::endl;
		//std::cout << "Enemy Status " << i << " - " << enemyStatus[i] << std::endl;
	}
	//std::cout << "I have " << enemyList->size() << " spaceships";

}