#include <BearLibTerminal.h>
#include <cmath>
#include <iostream>
using namespace std;
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

//for random numbers
#include <ctime>
#include <cstdlib>

//set up the console. Don't modify this line!
Console out;

int main()
{
	srand(time(NULL)); 

	//Set up the window
    terminal_open();
  	terminal_set(SETUP_MESSAGE);
	
    //array that holds the game board "map"
    char gameBoard[NUM_BOARD_X][NUM_BOARD_Y] = {EMPTY};
    
    //Variables that determine the level setup/difficulty.  
    int numWalls = 8;
	int numPowerUps = 5; //number of power ups on the board
	int numPickUpsLeft = STARTING_PICK_UPS; //number of pick ups left. 
	int winX = 0, winY = 0;
	
	//create the level by changing the board 
	createLevel(numWalls, numPowerUps, STARTING_PICK_UPS, winX, winY, gameBoard); 
	
	//print the game instructions to the console before hand. 
	printStartInstructions(); 
	
	//These are values that update as the game goes on: 
	int keyEntered = TK_A; 
	int frozenCount = 0; //sets how long the goose is frozen for 
    int numLives = 3; //number of lives the player has
    bool won = false; // has the player won yet? 
    
    //Restart the level each iteration. Stop when no lives are left
    for(int lifeNum = numLives; lifeNum > ZERO_LIVES; lifeNum--)
    {
    	//print out the board
		printBoard(gameBoard);
	    	
	    //Initialize player
		Actor player(PLAYER_CHAR, gameBoard);  
		
		//Initialize goose
		Actor goose(MONSTER_CHAR, gameBoard);
	  	
	  	//Reset the num pick ups left each level. 
	  	numPickUpsLeft = STARTING_PICK_UPS; 
	  	
	  	//Output how many lives left each level. 
	  	outputLivesLeft(lifeNum); 
	
		//while escape not pressed, console not closed, and the player hasnt won nor been captured:
	    while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE && !captured(player, goose) && won == false)
		{
		    keyEntered = terminal_read(); // get player key press
	
	        if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
	        {
	        	//move the player based on the key 
	    	    movePlayer(keyEntered, player, gameBoard); 
	    	    
	    	    //Updates number of pickUps if the player finds one. 
	    	    pickUp(player, numPickUpsLeft, gameBoard); 
				
				//move the goose automatically 
	            moveGoose(goose, player, gameBoard); 
	            
	            /*make sure to replace the win character if a goose crosses
	            or if a player crosses while there are still pickups*/
	            winnerCharCrossed(winX, winY, goose, gameBoard);
	            
	            //Slows the goose down if the player finds a powerUp. 
	            powerUp(player, goose, frozenCount, gameBoard); 
	            
	            /*if the player has found all the pickUps 
				and they make it to the win location:*/
	            if(winner(player, gameBoard) && numPickUpsLeft == 0)
	        		won = true; 	
	        }
	  	}
  	}

	//when the game has ended:
    if (keyEntered != TK_CLOSE)
    {
		gameEndScreen(won,gameBoard);
		out.writeLine("Thanks for playing!");
	
    	// Wait until user closes the window
        while (terminal_read() != TK_CLOSE);
    }
    
	//game is done, close it  
    terminal_close();
    
}
