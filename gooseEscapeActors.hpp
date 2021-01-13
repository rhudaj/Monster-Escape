#ifndef GOOSE_ESCAPE_ACTORS
#define GOOSE_ESCAPE_ACTORS
#include <cmath>
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "random.hpp"

class Actor
{
  private:
    int actorChar;      
    int location_x, location_y;
    int speed; //num spaces moved each time 

  public:
    Actor()
    {
        actorChar = int('A');
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        speed = 1; 
        put_actor();
    }

    Actor(char initPlayerChar, char gameBoard[][NUM_BOARD_Y])
    {
    	int xPos = 0 , yPos = 0; 
    	do
    	{
    		xPos = randomX();
			yPos = randomY(); 
		}
    	while(gameBoard[xPos][yPos] != EMPTY); 
    	
        change_char(initPlayerChar);
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        speed = 1; 
        update_location(xPos, yPos);
    }
    
    int get_x() const
    {
        return location_x;
    }
    
    int get_y() const
    {
        return location_y;
    }
    
    int get_speed() const
    {
        return speed;
    }
    
    string get_location_string() const
    {
        char buffer[80];
        itoa(location_x,buffer,10);
        string formatted_location = "(" + string(buffer) + ",";
        itoa(location_y,buffer,10);
        formatted_location += string(buffer) + ")";
        return formatted_location;
    }
    
    void change_char(char new_actor_char)
    {
        actorChar = min(int('~'),max(int(new_actor_char),int(' ')));
    }
	
	//check if the actor will remain within the board
    bool can_move(int delta_x, int delta_y) const
    {
        int new_x = location_x + delta_x;
        int new_y = location_y + delta_y;

        return new_x >= MIN_BOARD_X && new_x <= MAX_BOARD_X && new_y >= MIN_BOARD_Y && new_y <= MAX_BOARD_Y;
    }

    void update_location(int delta_x, int delta_y)
    {
        if (can_move(delta_x, delta_y))
        {
            terminal_clear_area(location_x, location_y, 1, 1);
            location_x += delta_x;
            location_y += delta_y;
            put_actor();
        }
    }
    
    //change the speed 
    void updateSpeed(int newSpeed)
    {
    	speed = newSpeed; 
	}
    
    //put the actor on the screen 
    void put_actor() const
    {
        terminal_put(location_x, location_y, actorChar);
        terminal_refresh();
    }
    
    //find the distance between the actor and a point 
    double distanceBetween(int xPos, int yPos) const
	{
		double deltaX = get_x() - xPos, deltaY = get_y() - yPos; 
	
		return sqrt(pow(deltaX, 2) + pow(deltaY, 2)); 
	}
	
	//check if two actors have the same position 
	bool samePosition(Actor const & otherActor) const
	{
			return (location_x == otherActor.location_x && location_y == otherActor.location_y); 
	}
    
};

/*
This class pertains to the walls that are randomly generated on the game board. 
*/
class Wall
{
	private: 
		int startX; //starting x position 
		int startY; //starting y position 
		int length; //length from the start position 
		bool horizontal; //wether its horizontal or not 
		
	public:
		
		//when called it keeps on making a wall until it is acceptable. 
		Wall(char gameBoard[][NUM_BOARD_Y])
		{
			do
			{
			startX = randomX(); 
			startY = randomY(); 
			length = randomWallLength(); 
			horizontal = randomBool(); 
			}
			while(!acceptableWall(gameBoard)); 
		}
		
		/*returns wether or not a positon of a newly placed brick on a wall is
		too within 'range' positions of another wall. If it is, the wall is 'too 
		close' and the function returns false. The goal is to have walls that are 
		spaced out and not clumped up on the map. 
		*/
		bool tooClose(int xPos, int yPos, char gameBoard[][NUM_BOARD_Y])
		{
			bool _tooClose = false;
			
			//Each option coresponds to a direction from the positon (xPos, yPos)
			for(int optionNum = 0; optionNum < NUM_OPTIONS; optionNum++)
			{
				int xOffset = 0, yOffset = 0; //the offset from the position. 
				
				if(optionNum == 0) 
					xOffset++; //to the right 
				else if(optionNum == 1) 
					xOffset--; //to the left
				else if(optionNum == 2)
					yOffset++; //down
				else if(optionNum == 3)
					yOffset--;  //up
			
				/*for each option(right, left, down, up) search for a specefied distance(dist)
				in that direction. If a wall is found to be there. Then the given position 
				is not valid for a brick of a wall. 
				*/
				for(int dist = 1; dist <= MIN_WALL_SPACING; dist++)
					if(gameBoard[xPos+dist*xOffset][yPos+dist*yOffset] == SHALL_NOT_PASS)
						_tooClose = true; 
			}
			return _tooClose; 
		}
		
		//A wall is 'acceptable' if it is not too close to other walls. 
		bool acceptableWall(char gameBoard[][NUM_BOARD_Y])
		{
			bool acceptableWall = true;  
			
			/*these values will be multiplied to the index of the gameboard array
			in order to specify which direction to check in (horizontal or vertical)*/
			int xFactor = (int)horizontal, yFactor = (int)(!horizontal);  
			
				for(int brickNum = 0; brickNum < length; brickNum++)
				{
					//if any of the 'bricks' of the wall being laid down are too close, the wall is not acceptable 
					if(tooClose(startX + brickNum*xFactor, startY+ brickNum*yFactor, gameBoard)) //gameBoard[startX + brickNum*xFactor][startY+ brickNum*yFactor] == SHALL_NOT_PASS
					{
						acceptableWall = false; //the wall is not acceptable 
						break; //no need to keep checking. 
					}
				}
	
			return acceptableWall; 	 	
		}

		//checks if a position is within the game board 
		bool withinBoard(int posX, int posY)
		{
			return posX >= MIN_BOARD_X && posX <= MAX_BOARD_X && posY >= MIN_BOARD_Y && posY <= MAX_BOARD_Y; 
		}
		
		//update the board with a wall 
		void putOnBoard(char gameBoard[][NUM_BOARD_Y])
		{	
			int horizontalIncrement = 0, verticalIncrement = 0; 
			int nextBrickX = startX, nextBrickY = startY; //position of the first brick 
			
			/*if the wall is horizontal, increment along the array horizontally. 
			Else, do it vertically*/
			if(horizontal)
				horizontalIncrement = RIGHT_ONE; 
			else
				verticalIncrement = DOWN_ONE;
			
			/*For the length of the wall. lay down each brick
			in the direction based on horizontal/vertical increment*/
			for(int brickNum = 0; brickNum < length; brickNum++)
			{
				nextBrickX+= horizontalIncrement;
				nextBrickY+= verticalIncrement;
				
				if(withinBoard(nextBrickX, nextBrickY))
		    		gameBoard[nextBrickX][nextBrickY] = SHALL_NOT_PASS;
			}
		}
};

#endif
