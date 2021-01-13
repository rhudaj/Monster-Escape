#ifndef GOOSE_ESCAPE_GAMEPLAY
#define GOOSE_ESCAPE_GAMEPLAY
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"

//Setting Up and Displaying the board to the screen:

	//Create Several Walls at Random 
	void createWalls(int numWalls, char gameBoard[][NUM_BOARD_Y]);

	//create a win location at random. Store the win location in variables in main. 	
	void createWinLocation(int & winX, int & winY, char gameBoard[][NUM_BOARD_Y]); 

	//create power up at a location
	void createPowerUp(int xPos, int yPos, char gameBoard[][NUM_BOARD_Y]);
	
	//create many power ups, calling the above function and passing a random location
	void createPowerUps(char gameBoard[][NUM_BOARD_Y], int numPowerUps); 
	
	//create a pickup at a random location
	void createPickUp(char gameBoard[][NUM_BOARD_Y]); 

	//create a specified number of pickups 
	void createPickUps(char gameBoard[][NUM_BOARD_Y], int numPickUps); 
	
	// print the game board to the screen 
	void printBoard(char gameBoard[][NUM_BOARD_Y]); 	
	
	//combines all of the above functions into a single function call. 
	void createLevel(int numWalls, int numPowerUps, int numPickUps, int & winX, int & winY, char gameBoard[][NUM_BOARD_Y]); 
	
//Moving Actors: 

	//move the goose
	void moveGoose(Actor & goose, Actor & player, char gameBoard[][NUM_BOARD_Y]);

	//move the player
	void movePlayer(int key, Actor & player, char gameBoard[][NUM_BOARD_Y]); /*add any other parameters */

//Functions to check if things are pick up / crossed: 

	//called when a power up is picked up 
	void powerUp(Actor & player, Actor & goose, int & frozenCount, char gameBoard[][NUM_BOARD_Y]); 

	//Called when the player is captured(does nothing yet) 
	bool captured(Actor const & player, Actor const & monster);

	//Check if the player hit the win location and picked up all the pickups. 
	bool winner(Actor & player, char gameBoard[][NUM_BOARD_Y]); 

	//maintaining the position of the WINNING char after it is crossed by the goose. 
	void winnerCharCrossed(int winX, int winY, Actor & goose, char gameBoard[][NUM_BOARD_Y]);

	//check if the player found a pickup. Update the num pickups 
	void pickUp(Actor & player, int & numPickUps, char gameBoard[][NUM_BOARD_Y]); 

//Game End States (Win or Loss): 

	//called when the player lost/won
	void  gameEndScreen(bool won, char gameBoard[][NUM_BOARD_Y]); 

//Output to the console:

	//print the starting instructions to the console 
	void printStartInstructions();	

	//let the player known how many lives they have left 
	void outputLivesLeft(int lifeNum);

	//let the player known how many pickups are left 
	void outputPickUpsLeft(int numPickUps);
	
	
//other

	//turn the player health into a string 
	string getHealthString(int numLives); 
	
	
	

#endif
