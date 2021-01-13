#include <iostream>
#include <cmath>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"
#include "random.hpp"

extern Console out;

//Setting Up and Displaying the board to the screen:

	//Create Several Walls at Random 
	void createWalls(int numWalls, char gameBoard[][NUM_BOARD_Y])
	{
		for(int wallNum = 0; wallNum < numWalls; wallNum++)
		{
			Wall wall1(gameBoard);
			
			wall1.putOnBoard(gameBoard); 
	
		}
	}

	//create a win location at random. Store the win location in variables in main. 	
	void createWinLocation(int & winX, int & winY, char gameBoard[][NUM_BOARD_Y])
	{
		do
		{
			winX = randomX();
			winY = randomY(); 
		}
		while(gameBoard[winX][winY] != EMPTY);
		
		gameBoard[winX][winY] = WIN_CHAR;
	}

	//create power up at a location
	void createPowerUp(char gameBoard[][NUM_BOARD_Y])
	{
		int xPos = randomX(), yPos = randomY(); 
		while(gameBoard[xPos][yPos] != EMPTY)
		{
			xPos = randomX();
			yPos = randomY(); 
		}
		gameBoard[xPos][yPos] = POWERUP_CHAR;
	}

	//create many power ups, calling the above function and passing a random location
	void createPowerUps(char gameBoard[][NUM_BOARD_Y], int numPowerUps)
	{
		for(int powerUpNum = 0; powerUpNum < numPowerUps; powerUpNum++)
			createPowerUp(gameBoard); 
	}

	
	//create a pickup at a random location
	void createPickUp(char gameBoard[][NUM_BOARD_Y])
	{
		int xPos = randomX(), yPos = randomY(); 
		while(gameBoard[xPos][yPos] != EMPTY)
		{
			xPos = randomX();
			yPos = randomY(); 
		}
		gameBoard[xPos][yPos] = PICKUP_CHAR;
	}

	//create a specified number of pickups 
	void createPickUps(char gameBoard[][NUM_BOARD_Y], int numPickUps)
	{
		for(int pickUpNum = 0; pickUpNum < numPickUps; pickUpNum++)
			createPickUp(gameBoard); 
	}
		
	// print the game board to the screen 
	void printBoard(char gameBoard[][NUM_BOARD_Y])
	{
		for(int boardX = MIN_BOARD_X; boardX < NUM_BOARD_X; boardX++)
		{
			for(int boardY = MIN_BOARD_Y; boardY < NUM_BOARD_Y; boardY++)
			{
				terminal_put(boardX, boardY, gameBoard[boardX][boardY]);
			}
		}
	}
	
	//combines all of the above functions into a single function call. 
	void createLevel(int numWalls, int numPowerUps, int numPickUps, int & winX, int & winY, char gameBoard[][NUM_BOARD_Y])
	{
		//build walls	
		createWalls(numWalls, gameBoard); 
		
		//create PowerUps at random location(s) 
		createPowerUps(gameBoard, numPowerUps); 
		
		//create pick ups
		createPickUps(gameBoard, numPickUps); 
	
		//create win location(s) 
		createWinLocation(winX, winY, gameBoard);
	}
	
//Moving Actors: 

	//move the goose
	void moveGoose(Actor & goose, Actor & player, char gameBoard[][NUM_BOARD_Y]) 
	{
		    double smallestDistance = goose.distanceBetween(player.get_x(), player.get_y()); 
			int xToMove = 0, yToMove = 0; 
			
			for(int optionNum = 0; optionNum < 4; optionNum++)
			{
				int xMove = 0, yMove = 0; //store the current move option 
				
				if(optionNum == 0) //option to move right
					xMove+=goose.get_speed();
				else if(optionNum == 1) //option to move left
					xMove-=goose.get_speed(); 
				else if(optionNum == 2) //option to move up
					yMove-=goose.get_speed();
				else if(optionNum == 3) //option to move down
					yMove+=goose.get_speed(); 
					
				//store the new location based on the option 
				int newXLocation = goose.get_x()+xMove;
				int newYLocation = goose.get_y()+yMove; 
				
				double currentOptionDistance = player.distanceBetween(newXLocation, newYLocation); 
				
				if(currentOptionDistance < smallestDistance && gameBoard[newXLocation][newYLocation] != SHALL_NOT_PASS)
				{
					smallestDistance = currentOptionDistance; 
					xToMove = xMove;
					yToMove = yMove; 
				}
			}
			
			if (goose.can_move(xToMove, yToMove))
		    	goose.update_location(xToMove, yToMove);		
	}

	//move the player
	void movePlayer(int key, Actor & player, char gameBoard[][NUM_BOARD_Y]) 
	{
	    int yMove = 0, xMove = 0;
	    
	    if (key == TK_UP)
	        yMove = -player.get_speed();
	    else if (key == TK_DOWN)
	        yMove = player.get_speed();
	    else if (key == TK_LEFT)
	        xMove = -player.get_speed();
	    else if (key == TK_RIGHT)
	        xMove = player.get_speed();
	    
	    int newXLocation = xMove+player.get_x();
	    int newYLocation = yMove+player.get_y(); 
	    
	    if (player.can_move(xMove, yMove) && gameBoard[newXLocation][newYLocation] != SHALL_NOT_PASS)
	        player.update_location(xMove, yMove);
	}

//Functions to check if things are pick up / crossed: 

	//called when a power up is picked up 
	void powerUp(Actor & player, Actor & goose, int & frozenCount, char gameBoard[][NUM_BOARD_Y])
	{	
		if(gameBoard[player.get_x()][player.get_y()] == POWERUP_CHAR)
			goose.updateSpeed(0); 
			
		if(goose.get_speed() == 0)
		{
			frozenCount++; 
			cout << frozenCount << endl; 
			if(frozenCount%5 == 0)
				goose.updateSpeed(1);
		}
			
	}
	
	//Called when the player is captured(does nothing yet) 
	bool captured(Actor const & player, Actor const & monster)
	{
		return (player.samePosition(monster)); 
	} 

	//Check if the player hit the win location and picked up all the pickups. 
	bool winner(Actor & player, char gameBoard[][NUM_BOARD_Y])
	{
		if(gameBoard[player.get_x()][player.get_y()] == WIN_CHAR)
			return true; 
		else
			return false; 
	}

	//maintaining the position of the WINNING char after it is crossed by the goose. 
	void winnerCharCrossed(int winX, int winY, Actor & goose, char gameBoard[][NUM_BOARD_Y])
	{
		bool crossed = false;
		
		if(goose.get_x() == winX && goose.get_y() == winY)
			crossed = true; 	
	
		if(!crossed)
		{
			gameBoard[winX][winY] = WIN_CHAR;
			terminal_put(winX, winY, gameBoard[winX][winY]); 
		}
	}

	//check if the player found a pickup. Update the num pickups 
	void pickUp(Actor & player, int & numPickUps, char gameBoard[][NUM_BOARD_Y])
	{	
		if(gameBoard[player.get_x()][player.get_y()] == PICKUP_CHAR)
		{
			numPickUps--; 
			outputPickUpsLeft(numPickUps); 
		}
	}


//Game End States (Win or Loss): 

	void clearBoard(char gameBoard[][NUM_BOARD_Y])
	{
		for(int x = 0; x < NUM_BOARD_X; x++)
			for(int y = 0; y < NUM_BOARD_Y; y++)
				gameBoard[x][y] = EMPTY;
	}

	//called when the player lost / Won
	void gameEndScreen(bool won,char gameBoard[][NUM_BOARD_Y])
	{
		
		clearBoard(gameBoard); 
		
		int textLength = sizeof(gameOver); 
		int startXIndex = NUM_BOARD_X/2 - (textLength/2); 
		
		if(won)
		{
			textLength = sizeof(nextLevelText); 
			startXIndex = NUM_BOARD_X/2 - (textLength/2); 
			
			for(int i = 0; i < textLength; i++)
				gameBoard[startXIndex+i][NUM_BOARD_Y/2] = nextLevelText[i]; 
		}
		else
		{
			for(int i = 0; i < textLength; i++)
				gameBoard[startXIndex+i][NUM_BOARD_Y/2] = gameOver[i]; 
		}
	
		printBoard(gameBoard); 
	}

//Output to the console:

	//print the starting instructions to the console 
	void printStartInstructions()
	{
		// Printing the instructions
		out.writeLine("Escape the Goose! If the goose catches you, you lose!");
		out.writeLine("Use the arrow keys to move. Collect Power Ups to slow the goose down");
		out.writeLine("You must save everyone before you can win!");
	}

	//let the player known how many lives they have left 
	void outputLivesLeft(int lifeNum)
	{
		string additionalText = " lives left!"; 
		
		if (lifeNum == 1)
			additionalText = " life left!";  
			
		out.writeLine(getHealthString(lifeNum) + additionalText);	
	}

	//let the player known how many pickups are left 
	void outputPickUpsLeft(int numPickUps)
	{
		string text = getHealthString(numPickUps) + " people left!"; 
		
		if (numPickUps == 1)
			text = getHealthString(numPickUps) + " person left!";  
		else if(numPickUps == 0)
			text = "No people left, get to the win location!";  
			
		out.writeLine(text);	
	}
	
//other

	//turn the player health into a string 
	string getHealthString(int numLives)
	{
		char buffer[80]; 
		itoa(numLives, buffer, 10);
		return string(buffer); 
	}


































